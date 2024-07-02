#include "utils_p.h"

#include <algorithm>

namespace SysCmdLine::Utils {

    std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
        std::vector<std::string> tokens;
        std::string::size_type start = 0;
        std::string::size_type end = s.find(delimiter);
        while (end != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + delimiter.size();
            end = s.find(delimiter, start);
        }
        tokens.push_back(s.substr(start));
        return tokens;
    }

    std::string join(const std::vector<std::string> &v, const std::string &delimiter) {
        if (v.empty())
            return {};

        std::string res;
        for (int i = 0; i < v.size() - 1; ++i) {
            res.append(v[i]);
            res.append(delimiter);
        }
        res.append(v.back());
        return res;
    }

    std::string formatText(const std::string &format, const std::vector<std::string> &args) {
        std::string result = format;
        for (size_t i = 0; i < args.size(); i++) {
            std::string placeholder = "%" + std::to_string(i + 1);
            size_t pos = result.find(placeholder);
            while (pos != std::string::npos) {
                result.replace(pos, placeholder.length(), args[i]);
                pos = result.find(placeholder, pos + args[i].size());
            }
        }
        return result;
    }

    static int levenshteinDistance(const std::string &s1, const std::string &s2) {
        auto len1 = s1.size();
        auto len2 = s2.size();

        // Alloc
        int **dp = new int *[len1 + 1];
        for (int i = 0; i <= len1; i++) {
            dp[i] = new int[len2 + 1];
        }

        for (int i = 0; i <= len1; i++) {
            for (int j = 0; j <= len2; j++) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }

        int res = dp[len1][len2];

        // Free
        for (int i = 0; i <= len1; i++) {
            delete[] dp[i];
        }
        delete[] dp;

        return res;
    }

    std::vector<std::string> calcClosestTexts(const std::vector<std::string> &texts,
                                              const std::string &input, int threshold) {

        std::vector<std::string> suggestions;
        for (const auto &cmd : texts) {
            int distance = levenshteinDistance(input, cmd);
            if (distance <= threshold) {
                suggestions.push_back(cmd);
            }
        }
        return suggestions;
    }

    std::string toUpper(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }

    std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

}