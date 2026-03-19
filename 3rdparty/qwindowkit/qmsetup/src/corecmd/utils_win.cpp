#include "utils.h"

#include <shlwapi.h>

#include <delayimp.h>

#include <windows.h>

#include <algorithm>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include <utility>

#include <syscmdline/system.h>

namespace SCL = SysCmdLine;

namespace fs = std::filesystem;

namespace Utils {

    static constexpr const DWORD g_EnglishLangId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

    static std::wstring winErrorMessage(uint32_t error, bool nativeLanguage = true) {
        std::wstring rc;
        wchar_t *lpMsgBuf;

        DWORD len = ::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                         FORMAT_MESSAGE_IGNORE_INSERTS,
                                     NULL, error, nativeLanguage ? 0 : g_EnglishLangId,
                                     reinterpret_cast<LPWSTR>(&lpMsgBuf), 0, NULL);

        if (len) {
            // Remove tail line breaks
            if (lpMsgBuf[len - 1] == L'\n') {
                lpMsgBuf[len - 1] = L'\0';
                if (len > 2 && lpMsgBuf[len - 2] == L'\r') {
                    lpMsgBuf[len - 2] = L'\0';
                }
            }
            rc = std::wstring(lpMsgBuf, int(len));
            ::LocalFree(lpMsgBuf);
        } else {
            rc += L"unknown error";
        }

        return rc;
    }

    static std::wstring quoteAndEscapeArg(const std::wstring &arg) {
        if (arg.find_first_of(L" \t\"") == std::wstring::npos) {
            // No need to quote or escape
            return arg;
        }

        std::wstring escapedArg = L"\"";
        for (auto ch : arg) {
            if (ch == L'"') {
                // Escape double quotes
                escapedArg += L"\"\"";
            } else {
                escapedArg += ch;
            }
        }
        escapedArg += L"\"";
        return escapedArg;
    }

    std::wstring executeCommand(const std::wstring &command,
                                const std::vector<std::wstring> &args) {
        SECURITY_ATTRIBUTES sa;
        HANDLE hReadPipe, hWritePipe;
        STARTUPINFOW si;
        PROCESS_INFORMATION pi;
        DWORD read;
        wchar_t buffer[4096]; // For captured output

        // Initialize security attributes to allow pipe handles to be inherited.
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.bInheritHandle = TRUE;
        sa.lpSecurityDescriptor = NULL;

        // Create a pipe for the child process's STDOUT.
        if (!::CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
            throw std::runtime_error("failed to call \"CreatePipe\": " +
                                     SCL::wideToUtf8(winErrorMessage(::GetLastError())));
        }

        // Ensure the read handle to the pipe for STDOUT is not inherited.
        if (!::SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0)) {
            ::CloseHandle(hWritePipe);
            ::CloseHandle(hReadPipe);
            throw std::runtime_error("failed to call \"SetHandleInformation\": " +
                                     SCL::wideToUtf8(winErrorMessage(::GetLastError())));
        }

        // Set up members of the STARTUPINFO structure.
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        si.hStdError = hWritePipe;
        si.hStdOutput = hWritePipe;
        si.dwFlags |= STARTF_USESTDHANDLES;

        // Construct command line
        std::wstringstream cmdLineStream;
        cmdLineStream << quoteAndEscapeArg(command) << L" ";
        for (const auto &arg : args) {
            cmdLineStream << quoteAndEscapeArg(arg) << L" ";
        }
        std::wstring cmdLine = cmdLineStream.str();

        // Start the child process.
        if (!::CreateProcessW(NULL, cmdLine.data(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
            ::CloseHandle(hWritePipe);
            ::CloseHandle(hReadPipe);

            throw std::runtime_error("failed to call \"CreateProcess\": " +
                                     SCL::wideToUtf8(winErrorMessage(::GetLastError())));
        }

        // Close the write end of the pipe before reading from the read end of the pipe.
        ::CloseHandle(hWritePipe);

        // Read output from the child process's pipe for STDOUT
        // and write to the parent process's STDOUT.
        std::wstring output;
        while (true) {
            if (!::ReadFile(hReadPipe, buffer, sizeof(buffer) - sizeof(wchar_t), &read, NULL) ||
                read == 0)
                break;

            buffer[read / sizeof(wchar_t)] = L'\0';
            output += buffer;
        }

        // Wait until child process exits.
        ::WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode;
        ::GetExitCodeProcess(pi.hProcess, &exitCode);

        // Close process and thread handles and the read end of the pipe.
        ::CloseHandle(pi.hProcess);
        ::CloseHandle(pi.hThread);
        ::CloseHandle(hReadPipe);

        if (exitCode == 0)
            return output;

        throw std::runtime_error(SCL::wideToUtf8(output));
    }

    // Helper functions to convert between FILETIME and std::chrono::system_clock::time_point
    static std::chrono::system_clock::time_point filetime_to_timepoint(const FILETIME &ft) {
        // Windows file time starts from January 1, 1601
        // std::chrono::system_clock starts from January 1, 1970
        static constexpr const long long WIN_EPOCH =
            116444736000000000LL; // in hundreds of nanoseconds
        long long duration = (static_cast<long long>(ft.dwHighDateTime) << 32) + ft.dwLowDateTime;
        duration -= WIN_EPOCH; // convert to Unix epoch
        return std::chrono::system_clock::from_time_t(duration / 10000000LL);
    }

    static FILETIME timepoint_to_filetime(const std::chrono::system_clock::time_point &tp) {
        FILETIME ft;
        static constexpr const long long WIN_EPOCH =
            116444736000000000LL; // in hundreds of nanoseconds
        long long duration =
            std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch()).count();
        duration = duration * 10 + WIN_EPOCH;
        ft.dwLowDateTime = static_cast<DWORD>(duration & 0xFFFFFFFF);
        ft.dwHighDateTime = static_cast<DWORD>((duration >> 32) & 0xFFFFFFFF);
        return ft;
    }

    FileTime fileTime(const fs::path &path) {
        HANDLE hFile = ::CreateFileW(path.wstring().data(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                                     OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("invalid path: \"" + SCL::wideToUtf8(path.wstring()) + "\"");
        }

        FILETIME creationTime, lastAccessTime, lastWriteTime;
        if (!::GetFileTime(hFile, &creationTime, &lastAccessTime, &lastWriteTime)) {
            ::CloseHandle(hFile);
            throw std::runtime_error("failed to get file time: \"" +
                                     SCL::wideToUtf8(path.wstring()) + "\"");
        }
        ::CloseHandle(hFile);

        FileTime times;
        // ... (convert FILETIMEs to std::chrono::system_clock::time_point and store in times)
        times.accessTime = filetime_to_timepoint(lastAccessTime);
        times.modifyTime = filetime_to_timepoint(lastWriteTime);
        times.statusChangeTime = filetime_to_timepoint(creationTime);

        return times;
    }

    void setFileTime(const fs::path &path, const FileTime &times) {
        HANDLE hFile = ::CreateFileW(path.wstring().data(), FILE_WRITE_ATTRIBUTES, FILE_SHARE_WRITE,
                                     nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hFile == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("invalid path: \"" + SCL::wideToUtf8(path.wstring()) + "\"");
        }

        FILETIME creationTime, lastAccessTime, lastWriteTime;
        lastAccessTime = timepoint_to_filetime(times.accessTime);
        lastWriteTime = timepoint_to_filetime(times.modifyTime);
        creationTime = timepoint_to_filetime(times.statusChangeTime);

        if (!::SetFileTime(hFile, &creationTime, &lastAccessTime, &lastWriteTime)) {
            ::CloseHandle(hFile);
            throw std::runtime_error("failed to set file time: \"" +
                                     SCL::wideToUtf8(path.wstring()) + "\"");
        }
        ::CloseHandle(hFile);
    }

    std::vector<std::filesystem::path> getPathsFromEnv() {
        DWORD length = ::GetEnvironmentVariableW(L"PATH", nullptr, 0);
        if (length == 0) {
            return {};
        }

        auto buf = new wchar_t[length];
        ::GetEnvironmentVariableW(L"PATH", buf, length);

        std::wstring pathStr = buf;
        delete[] buf;
        std::wstringstream wss(pathStr);
        std::wstring item;

        std::vector<fs::path> paths;
        while (std::getline(wss, item, L';')) {
            if (!item.empty()) {
                paths.push_back(item);
            }
        }
        return paths;
    }

    // ================================================================================
    // Modified from windeployqt 5.15.2(Copyright Qt company)
    // ================================================================================
    namespace WindowsDeployQt {

        static inline std::string stringFromRvaPtr(const void *rvaPtr) {
            return static_cast<const char *>(rvaPtr);
        }

        // Helper for reading out PE executable files: Find a section header for an RVA
        // (IMAGE_NT_HEADERS64, IMAGE_NT_HEADERS32).
        template <class ImageNtHeader>
        static const IMAGE_SECTION_HEADER *findSectionHeader(DWORD rva,
                                                             const ImageNtHeader *nTHeader) {
            const IMAGE_SECTION_HEADER *section = IMAGE_FIRST_SECTION(nTHeader);
            const IMAGE_SECTION_HEADER *sectionEnd =
                section + nTHeader->FileHeader.NumberOfSections;
            for (; section < sectionEnd; ++section)
                if (rva >= section->VirtualAddress &&
                    rva < (section->VirtualAddress + section->Misc.VirtualSize))
                    return section;
            return 0;
        }

        // Helper for reading out PE executable files: convert RVA to pointer (IMAGE_NT_HEADERS64,
        // IMAGE_NT_HEADERS32).
        template <class ImageNtHeader>
        inline const void *rvaToPtr(DWORD rva, const ImageNtHeader *nTHeader,
                                    const void *imageBase) {
            const IMAGE_SECTION_HEADER *sectionHdr = findSectionHeader(rva, nTHeader);
            if (!sectionHdr)
                return 0;
            const DWORD delta = sectionHdr->VirtualAddress - sectionHdr->PointerToRawData;
            return static_cast<const char *>(imageBase) + rva - delta;
        }

        // Helper for reading out PE executable files: return word size of a IMAGE_NT_HEADERS64,
        // IMAGE_NT_HEADERS32
        template <class ImageNtHeader>
        static unsigned ntHeaderWordSize(const ImageNtHeader *header) {
            // defines IMAGE_NT_OPTIONAL_HDR32_MAGIC, IMAGE_NT_OPTIONAL_HDR64_MAGIC
            enum { imageNtOptionlHeader32Magic = 0x10b, imageNtOptionlHeader64Magic = 0x20b };
            if (header->OptionalHeader.Magic == imageNtOptionlHeader32Magic)
                return 32;
            if (header->OptionalHeader.Magic == imageNtOptionlHeader64Magic)
                return 64;
            return 0;
        }

        // Helper for reading out PE executable files: Retrieve the NT image header of an
        // executable via the legacy DOS header.
        static IMAGE_NT_HEADERS *getNtHeader(void *fileMemory, std::wstring *errorMessage) {
            IMAGE_DOS_HEADER *dosHeader = static_cast<PIMAGE_DOS_HEADER>(fileMemory);
            // Check DOS header consistency
            if (IsBadReadPtr(dosHeader, sizeof(IMAGE_DOS_HEADER)) ||
                dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
                *errorMessage = L"DOS header check failed.";
                return 0;
            }
            // Retrieve NT header
            char *ntHeaderC = static_cast<char *>(fileMemory) + dosHeader->e_lfanew;
            IMAGE_NT_HEADERS *ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS *>(ntHeaderC);
            // check NT header consistency
            if (IsBadReadPtr(ntHeaders, sizeof(ntHeaders->Signature)) ||
                ntHeaders->Signature != IMAGE_NT_SIGNATURE ||
                IsBadReadPtr(&ntHeaders->FileHeader, sizeof(IMAGE_FILE_HEADER))) {
                *errorMessage = L"NT header check failed.";
                return 0;
            }
            // Check magic
            if (!ntHeaderWordSize(ntHeaders)) {
                std::wostringstream ss;
                ss << "NT header check failed; magic " << ntHeaders->OptionalHeader.Magic
                   << " is invalid.";
                *errorMessage = ss.str();
                return 0;
            }
            // Check section headers
            IMAGE_SECTION_HEADER *sectionHeaders = IMAGE_FIRST_SECTION(ntHeaders);
            if (IsBadReadPtr(sectionHeaders, ntHeaders->FileHeader.NumberOfSections *
                                                 sizeof(IMAGE_SECTION_HEADER))) {
                *errorMessage = L"NT header section header check failed.";
                return 0;
            }
            return ntHeaders;
        }

        // Helper for reading out PE executable files: Read out import sections from
        // IMAGE_NT_HEADERS64, IMAGE_NT_HEADERS32.
        template <class ImageNtHeader>
        static std::vector<std::string> readImportSections(const ImageNtHeader *ntHeaders,
                                                           const void *base,
                                                           std::wstring *errorMessage) {
            // Get import directory entry RVA and read out
            const DWORD importsStartRVA =
                ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]
                    .VirtualAddress;
            if (!importsStartRVA) {
                *errorMessage = L"Failed to find IMAGE_DIRECTORY_ENTRY_IMPORT entry.";
                return {};
            }
            const IMAGE_IMPORT_DESCRIPTOR *importDesc =
                static_cast<const IMAGE_IMPORT_DESCRIPTOR *>(
                    rvaToPtr(importsStartRVA, ntHeaders, base));
            if (!importDesc) {
                *errorMessage = L"Failed to find IMAGE_IMPORT_DESCRIPTOR entry.";
                return {};
            }
            std::vector<std::string> result;
            for (; importDesc->Name; ++importDesc)
                result.push_back(stringFromRvaPtr(rvaToPtr(importDesc->Name, ntHeaders, base)));

            // Read delay-loaded DLLs, see http://msdn.microsoft.com/en-us/magazine/cc301808.aspx .
            // Check on grAttr bit 1 whether this is the format using RVA's > VS 6
            if (const DWORD delayedImportsStartRVA =
                    ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT]
                        .VirtualAddress) {
                const ImgDelayDescr *delayedImportDesc = static_cast<const ImgDelayDescr *>(
                    rvaToPtr(delayedImportsStartRVA, ntHeaders, base));
                for (; delayedImportDesc->rvaDLLName && (delayedImportDesc->grAttrs & 1);
                     ++delayedImportDesc)
                    result.push_back(
                        stringFromRvaPtr(rvaToPtr(delayedImportDesc->rvaDLLName, ntHeaders, base)));
            }

            return result;
        }

        template <class ImageNtHeader>
        static void determineDependentLibs(const ImageNtHeader *nth, const void *fileMemory,
                                           bool isMinGW,
                                           std::vector<std::string> *dependentLibrariesIn,
                                           std::wstring *errorMessage) {
            std::vector<std::string> dependentLibraries;
            if (dependentLibrariesIn)
                dependentLibraries = readImportSections(nth, fileMemory, errorMessage);
            if (dependentLibrariesIn)
                *dependentLibrariesIn = dependentLibraries;
        }

        // Read a PE executable and determine dependent libraries, word size.
        bool readPeExecutable(const std::wstring &peExecutableFileName, std::wstring *errorMessage,
                              std::vector<std::string> *dependentLibrariesIn, unsigned *wordSizeIn,
                              bool isMinGW, unsigned short *machineArchIn) {
            bool result = false;
            HANDLE hFile = NULL;
            HANDLE hFileMap = NULL;
            void *fileMemory = 0;

            if (dependentLibrariesIn)
                dependentLibrariesIn->clear();
            if (wordSizeIn)
                *wordSizeIn = 0;

            do {
                // Create a memory mapping of the file
                hFile = CreateFileW(peExecutableFileName.data(), GENERIC_READ, FILE_SHARE_READ,
                                    NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (hFile == INVALID_HANDLE_VALUE || hFile == NULL) {
                    std::wostringstream ss;
                    ss << L"Cannot open \"" << peExecutableFileName << L"\": "
                       << winErrorMessage(::GetLastError());
                    *errorMessage = ss.str();
                    break;
                }

                hFileMap = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
                if (hFileMap == NULL) {
                    std::wostringstream ss;
                    ss << L"Cannot create file mapping of \"" << peExecutableFileName << L"\": "
                       << winErrorMessage(::GetLastError());
                    *errorMessage = ss.str();
                    break;
                }

                fileMemory = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);
                if (!fileMemory) {
                    std::wostringstream ss;
                    ss << L"Cannot map \"" << peExecutableFileName << L"\": "
                       << winErrorMessage(::GetLastError());
                    *errorMessage = ss.str();
                    break;
                }

                const IMAGE_NT_HEADERS *ntHeaders = getNtHeader(fileMemory, errorMessage);
                if (!ntHeaders)
                    break;

                const unsigned wordSize = ntHeaderWordSize(ntHeaders);
                if (wordSizeIn)
                    *wordSizeIn = wordSize;
                if (wordSize == 32) {
                    determineDependentLibs(reinterpret_cast<const IMAGE_NT_HEADERS32 *>(ntHeaders),
                                           fileMemory, isMinGW, dependentLibrariesIn, errorMessage);
                } else {
                    determineDependentLibs(reinterpret_cast<const IMAGE_NT_HEADERS64 *>(ntHeaders),
                                           fileMemory, isMinGW, dependentLibrariesIn, errorMessage);
                }

                if (machineArchIn)
                    *machineArchIn = ntHeaders->FileHeader.Machine;

                result = true;
            } while (false);

            if (fileMemory)
                UnmapViewOfFile(fileMemory);

            if (hFileMap != NULL)
                CloseHandle(hFileMap);

            if (hFile != NULL && hFile != INVALID_HANDLE_VALUE)
                CloseHandle(hFile);

            return result;
        }

    }

    std::vector<std::wstring>
        resolveWinBinaryDependencies(const std::filesystem::path &path,
                                     const std::vector<std::filesystem::path> &searchingPaths,
                                     std::vector<std::string> *unparsed) {
        std::wstring errorMessage;
        std::vector<std::string> dependentLibrariesIn;
        unsigned wordSizeIn;
        bool isMinGW = false;
        unsigned short machineArchIn;
        if (!WindowsDeployQt::readPeExecutable(path, &errorMessage, &dependentLibrariesIn,
                                               &wordSizeIn, isMinGW, &machineArchIn)) {
            throw std::runtime_error(SCL::wideToUtf8(errorMessage));
        }

        // Search
        std::vector<std::wstring> result;
        for (const auto &item : std::as_const(dependentLibrariesIn)) {
            fs::path fullPath;
            for (const auto &dir : std::as_const(searchingPaths)) {
                fs::path targetPath = dir / item;
                if (fs::exists(targetPath)) {
                    fullPath = targetPath;
                    break;
                }
            }

            if (!fullPath.empty()) {
                result.push_back(fullPath);
                continue;
            }

            if (unparsed) {
                unparsed->push_back(item);
            }
        }
        return result;
    }
}
