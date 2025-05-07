#include "system.h"

#include <cstdarg>
#include <algorithm>
#include <limits>

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
    std::string wideToUtf8(const std::wstring &utf16Str) {
#ifdef _WIN32
        if (utf16Str.empty()) {
            return {};
        }
        const auto utf16Length = static_cast<int>(utf16Str.size());
        if (utf16Length >= (std::numeric_limits<int>::max)()) {
            return {};
        }
        const int utf8Length = ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16Str.data(),
                                                     utf16Length, nullptr, 0, nullptr, nullptr);
        if (utf8Length <= 0) {
            return {};
        }
        std::string utf8Str;
        utf8Str.resize(utf8Length);
        ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16Str.data(), utf16Length,
                              utf8Str.data(), utf8Length, nullptr, nullptr);
        return utf8Str;
#else
        return std::filesystem::path(utf16Str).string();
#endif
    }

    /*!
        Returns the UTF-8 multi-byte string converted from wide string.
    */
    std::wstring utf8ToWide(const std::string &utf8Str) {
#ifdef _WIN32
        if (utf8Str.empty()) {
            return {};
        }
        const auto utf8Length = static_cast<int>(utf8Str.size());
        if (utf8Length >= (std::numeric_limits<int>::max)()) {
            return {};
        }
        const int utf16Length = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8Str.data(),
                                                      utf8Length, nullptr, 0);
        if (utf16Length <= 0) {
            return {};
        }
        std::wstring utf16Str;
        utf16Str.resize(utf16Length);
        ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8Str.data(), utf8Length,
                              utf16Str.data(), utf16Length);
        return utf16Str;
#else
        return std::filesystem::path(utf8Str).wstring();
#endif
    }

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
        enum Color {
            NoColor,
            Red,
            Green,
            Yellow,
            White,
        };

        explicit PrintScopeGuard(Color color = NoColor, bool highlight = false)
            : needReset(color != NoColor) {
#ifdef _WIN32
            _codepage = ::GetConsoleOutputCP();
            ::SetConsoleOutputCP(CP_UTF8);

            if (color != NoColor) {
                WORD winColor = highlight ? FOREGROUND_INTENSITY : 0;
                switch (color) {
                    case Red:
                        winColor |= FOREGROUND_RED;
                        break;
                    case Green:
                        winColor |= FOREGROUND_GREEN;
                        break;
                    case Yellow:
                        winColor |= FOREGROUND_RED | FOREGROUND_GREEN;
                        break;
                    case White:
                        winColor |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
                    default:
                        break;
                }
                _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                GetConsoleScreenBufferInfo(_hConsole, &_csbi);
                SetConsoleTextAttribute(_hConsole, winColor);
            }
#else
            if (color != NoColor) {
                // ANSI escape code to set text color to red
                const char *colorStr;
                switch (color) {
                    case Red:
                        colorStr = highlight ? "\033[91m" : "\033[31m";
                        break;
                    case Green:
                        colorStr = highlight ? "\033[92m" : "\033[32m";
                        break;
                    case Yellow:
                        colorStr = highlight ? "\033[93m" : "\033[33m";
                        break;
                    case White:
                        colorStr = highlight ? "\033[97m" : "\033[37m";
                        break;
                    default:
                        break;
                }
                printf("%s", colorStr);
            }
#endif
        }

        ~PrintScopeGuard() {
#ifdef _WIN32
            ::SetConsoleOutputCP(_codepage);

            if (needReset) {
                SetConsoleTextAttribute(_hConsole, _csbi.wAttributes);
            }
#else
            if (needReset) {
                // ANSI escape code to reset text color to default
                const char *resetColor = "\033[0m";
                printf("%s", resetColor);
            }
#endif
        }

    private:
        bool needReset;
#ifdef _WIN32
        UINT _codepage;
        HANDLE _hConsole;
        CONSOLE_SCREEN_BUFFER_INFO _csbi;
#endif
    };

    /*!
        Prints the formatted text in UTF-8 with given message type.
    */
    int u8debug(MessageType messageType, bool highlight, const char *fmt, ...) {
        PrintScopeGuard::Color color;
        switch (messageType) {
            case MT_Information:
                color = PrintScopeGuard::White;
                break;
            case MT_Healthy:
                color = PrintScopeGuard::Green;
                break;
            case MT_Warning:
                color = PrintScopeGuard::Yellow;
                break;
            case MT_Critical:
                color = PrintScopeGuard::Red;
                break;
            default:
                color = PrintScopeGuard::NoColor;
                break;
        }
        PrintScopeGuard _guard(color, highlight);

        va_list args;
        va_start(args, fmt);
        int res = vprintf(fmt, args);
        va_end(args);
        return res;
    }

    /*!
        Prints the formatted text in UTF-8.
    */
    int u8printf(const char *fmt, ...) {
        PrintScopeGuard _guard;

        va_list args;
        va_start(args, fmt);
        int res = vprintf(fmt, args);
        va_end(args);
        return res;
    }

}