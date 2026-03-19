#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <vector>

namespace Utils {

    // Filesystem Utils
    struct FileTime {
        std::chrono::system_clock::time_point accessTime;
        std::chrono::system_clock::time_point modifyTime;
        std::chrono::system_clock::time_point statusChangeTime; // Creation time on Windows
    };

    FileTime fileTime(const std::filesystem::path &path);

    void setFileTime(const std::filesystem::path &path, const FileTime &times);

    inline void syncFileTime(const std::filesystem::path &dest, const std::filesystem::path &src) {
        setFileTime(dest, fileTime(src));
    }

    std::vector<std::filesystem::path> getPathsFromEnv();

    std::filesystem::path cleanPath(const std::filesystem::path &path);

    // String Utils
    template <class T>
    std::vector<std::basic_string<T>> split(const std::basic_string<T> &s,
                                            const std::basic_string<T> &delimiter) {
        std::vector<std::basic_string<T>> tokens;
        typename std::basic_string<T>::size_type start = 0;
        typename std::basic_string<T>::size_type end = s.find(delimiter);
        while (end != std::basic_string<T>::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + delimiter.size();
            end = s.find(delimiter, start);
        }
        tokens.push_back(s.substr(start));
        return tokens;
    }

    template <class T>
    std::basic_string<T> trim(const std::basic_string<T> &str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
            start++;
        }

        auto end = str.end();
        do {
            end--;
        } while (std::distance(start, end) > 0 && std::isspace(*end));

        return {start, end + 1};
    }

    template <class T>
    void replaceString(std::basic_string<T> &s, const std::basic_string<T> &pattern,
                       const std::basic_string<T> &text) {
        size_t idx = 0;
        while ((idx = s.find(pattern, idx)) != std::basic_string<T>::npos) {
            s.replace(idx, pattern.size(), text);
            idx += text.size();
        }
    };

    template <class T>
    std::basic_string<T> join(const std::vector<std::basic_string<T>> &v,
                              const std::basic_string<T> &delimiter) {
        if (v.empty())
            return {};

        std::basic_string<T> res;
        for (int i = 0; i < v.size() - 1; ++i) {
            res.append(v[i]);
            res.append(delimiter);
        }
        res.append(v.back());
        return res;
    }

    template <class T>
    std::basic_string<T> toLower(std::basic_string<T> s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    template <class T>
    std::basic_string<T> toUpper(std::basic_string<T> s) {
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }

    inline bool starts_with(const std::string_view &s, const std::string_view &prefix) {
#if __cplusplus >= 202002L
        return s.starts_with(prefix);
#else
        return s.size() >= prefix.size() && s.substr(0, prefix.size()) == prefix;
#endif
    }

    inline bool starts_with(const std::wstring_view &s, const std::wstring_view &prefix) {
#if __cplusplus >= 202002L
        return s.starts_with(prefix);
#else
        return s.size() >= prefix.size() && s.substr(0, prefix.size()) == prefix;
#endif
    }

    template <class Container, class T>
    inline bool contains(const Container &container, const T &key) {
#if __cplusplus >= 202002L
        return container.contains(key);
#else
        return container.count(key) != 0;
#endif
    }

    // OS Utils
#ifdef _WIN32
    std::wstring executeCommand(const std::wstring &command, const std::vector<std::wstring> &args);

    std::vector<std::wstring>
        resolveWinBinaryDependencies(const std::filesystem::path &path,
                                     const std::vector<std::filesystem::path> &searchingPaths,
                                     std::vector<std::string> *unparsed);
#else
    std::string executeCommand(const std::string &command, const std::vector<std::string> &args);

    void setFileRPaths(const std::string &file, const std::vector<std::string> &paths);

    std::vector<std::string>
        resolveUnixBinaryDependencies(const std::filesystem::path &path,
                                      const std::vector<std::filesystem::path> &searchingPaths,
                                      std::vector<std::string> *unparsed = nullptr);
#endif

#ifdef __APPLE__
    std::vector<std::string> getMacAbsoluteDependencies(const std::string &file);

    void replaceMacFileDependencies(
        const std::string &file, const std::vector<std::pair<std::string, std::string>> &depPairs);
#elif defined(__linux__)
    std::string getInterpreter(const std::string &file);

    bool setFileInterpreter(const std::string &file, const std::string &interpreter);
#endif
}


#endif // UTILS_H
