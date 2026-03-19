#include "system.h"

#include <algorithm>
#include <limits>
#include <mutex>
#include <cstring>
#include <cstdarg>

#ifdef _WIN32
#  include <windows.h>
#  include <shellapi.h>

#  include "utils_p.h"
#else
#  include <limits.h>
#  include <sys/stat.h>
#  include <utime.h>
#  ifdef __APPLE__
#    include <crt_externs.h>
#    include <mach-o/dyld.h>
#  else
#    include <fstream>
#  endif
#  include <filesystem>
#endif

#ifdef _WIN32
#  ifndef WC_ERR_INVALID_CHARS
#    define WC_ERR_INVALID_CHARS 0x00000080
#  endif
#endif

namespace SysCmdLine {

#ifdef _WIN32
    static std::wstring winGetFullModuleFileName(HMODULE hModule) {
        // Use stack buffer for the first try
        wchar_t stackBuf[MAX_PATH + 1];

        // Call
        wchar_t *buf = stackBuf;
        auto size = ::GetModuleFileNameW(nullptr, buf, MAX_PATH);
        if (size == 0) {
            return {};
        }
        if (size > MAX_PATH) {
            // Re-alloc
            buf = new wchar_t[size + 1]; // The return size doesn't contain the terminating 0

            // Call
            if (::GetModuleFileNameW(nullptr, buf, size) == 0) {
                delete[] buf;
                return {};
            }
        }

        std::replace(buf, buf + size, L'\\', L'/');

        // Return
        std::wstring res(buf);
        if (buf != stackBuf) {
            delete[] buf;
        }
        return res;
    }
#elif defined(__APPLE__)
    static std::string macGetExecutablePath() {
        // Use stack buffer for the first try
        char stackBuf[PATH_MAX + 1];

        // "_NSGetExecutablePath" will return "-1" if the buffer is not large enough
        // and "*bufferSize" will be set to the size required.

        // Call
        unsigned int size = PATH_MAX + 1;
        char *buf = stackBuf;
        if (_NSGetExecutablePath(buf, &size) != 0) {
            // Re-alloc
            buf = new char[size]; // The return size contains the terminating 0

            // Call
            if (_NSGetExecutablePath(buf, &size) != 0) {
                delete[] buf;
                return {};
            }
        }

        // Return
        std::string res(buf);
        if (buf != stackBuf) {
            delete[] buf;
        }
        return res;
    }
#endif

    /*!
        Returns the wide string converted from UTF-8 multi-byte string.
    */
    std::string wideToUtf8(const std::wstring &s) {
#ifdef _WIN32
        if (s.empty()) {
            return {};
        }
        const auto utf16Length = static_cast<int>(s.size());
        if (utf16Length >= (std::numeric_limits<int>::max)()) {
            return {};
        }
        const int utf8Length = ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, s.data(),
                                                     utf16Length, nullptr, 0, nullptr, nullptr);
        if (utf8Length <= 0) {
            return {};
        }
        std::string utf8Str;
        utf8Str.resize(utf8Length);
        ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, s.data(), utf16Length, utf8Str.data(),
                              utf8Length, nullptr, nullptr);
        return utf8Str;
#else
        return std::filesystem::path(s).string();
#endif
    }

    /*!
        Returns the UTF-8 multi-byte string converted from wide string.
    */
    std::wstring utf8ToWide(const std::string &s) {
#ifdef _WIN32
        if (s.empty()) {
            return {};
        }
        const auto utf8Length = static_cast<int>(s.size());
        if (utf8Length >= (std::numeric_limits<int>::max)()) {
            return {};
        }
        const int utf16Length =
            ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), utf8Length, nullptr, 0);
        if (utf16Length <= 0) {
            return {};
        }
        std::wstring utf16Str;
        utf16Str.resize(utf16Length);
        ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.data(), utf8Length, utf16Str.data(),
                              utf16Length);
        return utf16Str;
#else
        return std::filesystem::path(s).wstring();
#endif
    }

#ifdef _WIN32
    /*!
        Returns the UTF-8 multi-byte string converted from ANSI string.
    */
    std::string ansiToUtf8(const std::string &s) {
        if (s.empty()) {
            return {};
        }
        const auto ansiLength = static_cast<int>(s.size());
        if (ansiLength >= (std::numeric_limits<int>::max)()) {
            return {};
        }
        const int utf16Length =
            ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, s.data(), ansiLength, nullptr, 0);
        if (utf16Length <= 0) {
            return {};
        }
        std::wstring utf16Str;
        utf16Str.resize(utf16Length);
        ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, s.data(), ansiLength, utf16Str.data(),
                              utf16Length);
        return wideToUtf8(utf16Str);
    }
#endif

    /*!
        Returns the application file path, the path separator of which is <tt>/</tt>.
    */
    std::string appPath() {
        static const auto res = []() -> std::string {
#ifdef _WIN32
            return wideToUtf8(winGetFullModuleFileName(nullptr));
#elif defined(__APPLE__)
            return macGetExecutablePath();
#else
            char buf[PATH_MAX];
            if (!realpath("/proc/self/exe", buf)) {
                return {};
            }
            return buf;
#endif
        }();
        return res;
    }

    /*!
        Returns the application directory path, the path separator of which is <tt>/</tt>.
    */
    std::string appDirectory() {
        auto appDir = appPath();
        auto slashIdx = appDir.find_last_of('/');
        if (slashIdx != std::string::npos) {
            appDir = appDir.substr(0, slashIdx);
        }
        return appDir;
    }

    /*!
        Returns the application file name.
    */
    std::string appFileName() {
        auto appName = appPath();
        auto slashIdx = appName.find_last_of('/');
        if (slashIdx != std::string::npos) {
            appName = appName.substr(slashIdx + 1);
        }
        return appName;
    }

    /*!
        Returns the application name. On Windows, the file extension will be stripped.
    */
    std::string appName() {
        auto appName = appFileName();
#ifdef _WIN32
        auto dotIdx = appName.find_last_of('.');
        if (dotIdx != std::string::npos) {
            std::string suffix = Utils::toLower(appName.substr(dotIdx + 1));
            if (suffix == "exe") {
                appName = appName.substr(0, dotIdx);
            }
        }
#endif
        return appName;
    }

    /*!
        Returns the command line argument list in UTF-8.
    */
    std::vector<std::string> commandLineArguments() {
        std::vector<std::string> res;
#ifdef _WIN32
        int argc;
        auto argvW = ::CommandLineToArgvW(::GetCommandLineW(), &argc);
        if (argvW == nullptr)
            return {};
        res.reserve(argc);
        for (int i = 0; i != argc; ++i) {
            res.push_back(wideToUtf8(argvW[i]));
        }
        ::LocalFree(argvW);
#elif defined(__APPLE__)
        auto argv = *(_NSGetArgv());
        for (int i = 0; argv[i] != nullptr; ++i) {
            res.push_back(argv[i]);
        }
#else
        std::ifstream file("/proc/self/cmdline", std::ios::in);
        if (file.fail())
            return {};
        std::string s;
        while (std::getline(file, s, '\0')) {
            res.push_back(s);
        }
        file.close();
#endif
        return res;
    }

    class PrintScopeGuard {
    public:
        static std::mutex &global_mtx() {
            static std::mutex _instance;
            return _instance;
        }

        explicit PrintScopeGuard(int foreground, int background)
            : consoleChanged(!(foreground == DefaultColor && background == DefaultColor)) {
            global_mtx().lock();
#ifdef _WIN32
            _codepage = ::GetConsoleOutputCP();
            ::SetConsoleOutputCP(CP_UTF8);

            if (consoleChanged) {
                WORD winColor = 0;
                if (foreground != DefaultColor) {
                    winColor |= (foreground & Intensified) ? FOREGROUND_INTENSITY : 0;
                    switch (foreground & 0xF) {
                        case Red:
                            winColor |= FOREGROUND_RED;
                            break;
                        case Green:
                            winColor |= FOREGROUND_GREEN;
                            break;
                        case Blue:
                            winColor |= FOREGROUND_BLUE;
                            break;
                        case Yellow:
                            winColor |= FOREGROUND_RED | FOREGROUND_GREEN;
                            break;
                        case Purple:
                            winColor |= FOREGROUND_RED | FOREGROUND_BLUE;
                            break;
                        case Cyan:
                            winColor |= FOREGROUND_GREEN | FOREGROUND_BLUE;
                            break;
                        case White:
                            winColor |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
                        default:
                            break;
                    }
                }
                if (background != DefaultColor) {
                    winColor |= (background & Intensified) ? BACKGROUND_INTENSITY : 0;
                    switch (background & 0xF) {
                        case Red:
                            winColor |= BACKGROUND_RED;
                            break;
                        case Green:
                            winColor |= BACKGROUND_GREEN;
                            break;
                        case Blue:
                            winColor |= BACKGROUND_BLUE;
                            break;
                        case Yellow:
                            winColor |= BACKGROUND_RED | BACKGROUND_GREEN;
                            break;
                        case Purple:
                            winColor |= BACKGROUND_RED | BACKGROUND_BLUE;
                            break;
                        case Cyan:
                            winColor |= BACKGROUND_GREEN | BACKGROUND_BLUE;
                            break;
                        case White:
                            winColor |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
                        default:
                            break;
                    }
                }
                _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                GetConsoleScreenBufferInfo(_hConsole, &_csbi);
                SetConsoleTextAttribute(_hConsole, winColor);
            }
#else
            if (consoleChanged) {
                const char *strList[3];
                int strListSize = 0;
                if (foreground != DefaultColor) {
                    bool light = foreground & Intensified;
                    const char *colorStr = nullptr;
                    switch (foreground & 0xF) {
                        case Red:
                            colorStr = light ? "91" : "31";
                            break;
                        case Green:
                            colorStr = light ? "92" : "32";
                            break;
                        case Blue:
                            colorStr = light ? "94" : "34";
                            break;
                        case Yellow:
                            colorStr = light ? "93" : "33";
                            break;
                        case Purple:
                            colorStr = light ? "95" : "35";
                            break;
                        case Cyan:
                            colorStr = light ? "96" : "36";
                            break;
                        case White:
                            colorStr = light ? "97" : "37";
                            break;
                        default:
                            break;
                    }
                    if (colorStr) {
                        strList[strListSize] = colorStr;
                        strListSize++;
                    }
                }
                if (background != DefaultColor) {
                    bool light = background & Intensified;
                    const char *colorStr = nullptr;
                    switch (background & 0xF) {
                        case Red:
                            colorStr = light ? "101" : "41";
                            break;
                        case Green:
                            colorStr = light ? "102" : "42";
                            break;
                        case Blue:
                            colorStr = light ? "104" : "44";
                            break;
                        case Yellow:
                            colorStr = light ? "103" : "43";
                            break;
                        case Purple:
                            colorStr = light ? "105" : "45";
                            break;
                        case Cyan:
                            colorStr = light ? "106" : "46";
                            break;
                        case White:
                            colorStr = light ? "107" : "47";
                            break;
                        default:
                            break;
                    }
                    if (colorStr) {
                        strList[strListSize] = colorStr;
                        strListSize++;
                    }
                }
                if (strListSize > 0) {
                    char buf[20];
                    int bufSize = 0;
                    auto buf_puts = [&buf, &bufSize](const char *s) {
                        auto len = strlen(s);
                        for (; *s != '\0'; ++s) {
                            buf[bufSize++] = *s;
                        }
                    };
                    buf_puts("\033[");
                    for (int i = 0; i < strListSize - 1; ++i) {
                        buf_puts(strList[i]);
                        buf_puts(";");
                    }
                    buf_puts(strList[strListSize - 1]);
                    buf_puts("m");
                    buf[bufSize] = '\0';
                    printf("%s", buf);
                }
            }
#endif
        }

        ~PrintScopeGuard() {
#ifdef _WIN32
            ::SetConsoleOutputCP(_codepage);

            if (consoleChanged) {
                SetConsoleTextAttribute(_hConsole, _csbi.wAttributes);
            }
#else
            if (consoleChanged) {
                // ANSI escape code to reset text color to default
                const char *resetColor = "\033[0m";
                printf("%s", resetColor);
            }
#endif
            global_mtx().unlock();
        }

    private:
        bool consoleChanged;
#ifdef _WIN32
        UINT _codepage;
        HANDLE _hConsole;
        CONSOLE_SCREEN_BUFFER_INFO _csbi;
#endif
    };

    int u8printf(int foreground, int background, const char *fmt, ...) {
        PrintScopeGuard _guard(foreground, background);

        va_list args;
        va_start(args, fmt);
        int res = std::vprintf(fmt, args);
        va_end(args);
        return res;
    }

    int u8vprintf(int foreground, int background, const char *fmt, va_list args) {
        PrintScopeGuard _guard(foreground, background);
        return std::vprintf(fmt, args);
    }

    /*!
        Prints the formatted text in UTF-8 with given message type.
    */
    int u8debug(MessageType messageType, bool highlight, const char *fmt, ...) {
        int color;
        switch (messageType) {
            case MT_Message:
                color = White;
                break;
            case MT_Healthy:
                color = Green;
                break;
            case MT_Warning:
                color = Yellow;
                break;
            case MT_Critical:
                color = Red;
                break;
            default:
                color = DefaultColor;
                break;
        }
        if (highlight) {
            color |= Intensified;
        }

        va_list args;
        va_start(args, fmt);
        int res = u8vprintf(color, DefaultColor, fmt, args);
        va_end(args);
        return res;
    }


    int u8info(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        int res = u8vprintf(DefaultColor, DefaultColor, fmt, args);
        va_end(args);
        return res;
    }

}