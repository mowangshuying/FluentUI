#ifndef MAP_P_H
#define MAP_P_H

#include <map>
#include <string>
#include <vector>

namespace SysCmdLine {

    using StringList = std::vector<std::string>;

    using IntList = std::vector<int>;

    union Ele {
        int i;
        size_t s;
        IntList *il;
        StringList *sl;
        void *p;
    };

    inline Ele ele(int i) noexcept {
#if __cplusplus >= 202002L
        return Ele{.i = i};
#else
        Ele res;
        res.i = i;
        return res;
#endif
    }

    inline Ele ele(size_t s) noexcept {
#if __cplusplus >= 202002L
        return Ele{.s = s};
#else
        Ele res;
        res.s = s;
        return res;
#endif
    }

    inline Ele ele(IntList *il) noexcept {
#if __cplusplus >= 202002L
        return Ele{.il = il};
#else
        Ele res;
        res.il = il;
        return res;
#endif
    }

    inline Ele ele(StringList *sl) noexcept {
#if __cplusplus >= 202002L
        return Ele{.sl = sl};
#else
        Ele res;
        res.sl = sl;
        return res;
#endif
    }

    inline Ele ele(void *p) noexcept {
#if __cplusplus >= 202002L
        return Ele{.p = p};
#else
        Ele res;
        res.p = p;
        return res;
#endif
    }

    // Avoiding template specialization greatly helps to reduce the binary size,
    // so we only use this map in the library implementation.
    using GenericMap = std::map<std::string, Ele>;

    struct StringListMapWrapper {
        StringListMapWrapper() = default;

        StringListMapWrapper(const StringListMapWrapper &other) {
            for (const auto &pair : other.data) {
                data[pair.first] = ele(new StringList(*pair.second.sl));
            }
        }

        ~StringListMapWrapper() {
            for (const auto &pair : std::as_const(data)) {
                delete pair.second.sl;
            }
        }

        GenericMap data;
    };

    struct IntListMapWrapper {
        IntListMapWrapper() = default;

        IntListMapWrapper(const IntListMapWrapper &other) {
            for (const auto &pair : other.data) {
                data[pair.first] = ele(new IntList(*pair.second.il));
            }
        }

        ~IntListMapWrapper() {
            for (const auto &pair : std::as_const(data)) {
                delete pair.second.il;
            }
        }

        GenericMap data;
    };

}

#endif // MAP_P_H
