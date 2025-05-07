#include "utils.h"

namespace fs = std::filesystem;

#ifdef _WIN32
#  define _TSTR(X) L##X
#  define tstrcmp  wcscmp
#else
#  define _TSTR(X) X
#  define tstrcmp  strcmp
#endif

namespace Utils {

    std::filesystem::path cleanPath(const std::filesystem::path &path) {
        fs::path result;
        for (const auto &part : path) {
            if (part == _TSTR("..")) {
                if (!result.empty() && result.filename() != _TSTR("..")) {
                    result = result.parent_path();
                } else {
                    result /= part;
                }
            } else if (part != _TSTR(".")) {
                result /= part;
            }
        }
        return result;
    }

}