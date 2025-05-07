#include "utils.h"

#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utime.h>

#include <cstring>
#include <filesystem>
#include <regex>
#include <set>
#include <sstream>

namespace fs = std::filesystem;

namespace Utils {

    std::string executeCommand(const std::string &command, const std::vector<std::string> &args) {
        // printf("Executing command: %s", command.data());
        // for (const auto &arg : args) {
        //     printf(" %s", arg.data());
        // }
        // printf("\n");

        static const auto &dupStr = [](char *&dest, const char *src, size_t size) {
            dest = new char[size + 1];
            memcpy(dest, src, size);
            dest[size] = '\0';
        };

        enum PipeNum {
            PN_Read,
            PN_Write,
        };

        // Create pipe
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            throw std::runtime_error("failed to call \"pipe\"");
        }

        pid_t pid = fork();
        if (pid < 0) {
            // Close pipes right away
            close(pipefd[PN_Read]);
            close(pipefd[PN_Write]);
            throw std::runtime_error("failed to call \"fork\"");
        }

        if (pid == 0) {
            // --------
            // Child process
            // --------

            // Close read pipe
            close(pipefd[PN_Read]);

            // Redirect "stdout" and "stderr" to write pipe
            dup2(pipefd[PN_Write], STDOUT_FILENO);
            dup2(pipefd[PN_Write], STDERR_FILENO);

            // Prepare arguments
            auto argv = new char *[args.size() + 2]; // +2 for command and nullptr
            dupStr(argv[0], command.data(), command.size());
            for (size_t i = 0; i < args.size(); ++i) {
                dupStr(argv[i + 1], args[i].data(), args[i].size());
            }
            argv[args.size() + 1] = nullptr;

            // Call "exec"
            execvp(argv[0], argv);

            // If the control flow reaches here, there must be a mistake

            // Clean allocated memory
            for (size_t i = 0; i < args.size() + 2; ++i) {
                delete[] argv[i];
            }
            delete[] argv;

            // Fail
            printf("exec \"%s\" failed: %s\n", command.data(), strerror(errno));

            // No need to close write pipe, let the System handle everything
            // Simply exit
            exit(EXIT_FAILURE);
        }

        // --------
        // Parent process
        // --------

        // Close write pipe
        close(pipefd[PN_Write]);

        // Read child process output
        char buffer[256];
        std::string output;
        ssize_t bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            output += buffer;
        }

        // Close read pipe
        close(pipefd[PN_Read]);

        // Wait for child process to terminate
        int status;
        waitpid(pid, &status, 0);

        // Check exit status
        if (WIFEXITED(status)) {
            auto exitCode = WEXITSTATUS(status);
            if (exitCode == 0)
                return output;

            // Throw error
            throw std::runtime_error(trim(output));
        }

        if (WIFSIGNALED(status)) {
            auto sig = WTERMSIG(status);
            throw std::runtime_error("command \"" + command + "\" was terminated by signal " +
                                     std::to_string(sig));
        }

        throw std::runtime_error("command \"" + command + "\" terminated abnormally with status " +
                                 std::to_string(status));
    }

    FileTime fileTime(const fs::path &path) {
        struct stat sb;
        if (stat(path.c_str(), &sb) == -1) {
            throw std::runtime_error("failed to get file time: \"" + path.string() + "\"");
        }

        FileTime times;
        times.accessTime = std::chrono::system_clock::from_time_t(sb.st_atime);
        times.modifyTime = std::chrono::system_clock::from_time_t(sb.st_mtime);
        times.statusChangeTime = std::chrono::system_clock::from_time_t(sb.st_ctime);
        return times;
    }

    void setFileTime(const fs::path &path, const FileTime &times) {
        struct utimbuf new_times;
        new_times.actime = std::chrono::system_clock::to_time_t(times.accessTime);
        new_times.modtime = std::chrono::system_clock::to_time_t(times.modifyTime);
        if (utime(path.c_str(), &new_times) != 0) {
            throw std::runtime_error("failed to set file time: \"" + path.string() + "\"");
        }
    }

    std::vector<fs::path> getPathsFromEnv() {
        const char *pathEnv = std::getenv("PATH");
        if (pathEnv == nullptr) {
            return {};
        }

        std::string pathStr = pathEnv;
        std::stringstream ss(pathStr);
        std::string item;

        std::vector<fs::path> paths;
        while (std::getline(ss, item, ':')) {
            if (!item.empty()) {
                paths.push_back(fs::path(item));
            }
        }

        return paths;
    }

#ifdef __APPLE__
    // Mac
    // Use `otool` and `install_name_tool`

    static std::vector<std::string> readMacBinaryRPaths(const std::string &path) {
        std::vector<std::string> rpaths;
        std::string output;

        try {
            output = executeCommand("otool", {"-l", path});
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to get RPATHs: " + std::string(e.what()));
        }

        static const std::regex rpathRegex(R"(\s*path\s+(.*)\s+\(offset.*)");
        std::istringstream iss(output);
        std::string line;
        std::smatch match;

        while (std::getline(iss, line)) {
            if (line.find("cmd LC_RPATH") != std::string::npos) {
                // skip 2 lines
                std::getline(iss, line);
                std::getline(iss, line);
                if (std::regex_match(line, match, rpathRegex) && match.size() >= 2) {
                    rpaths.emplace_back(match[1].str());
                }
            }
        }

        return rpaths;
    }

    static std::vector<std::string> readMacBinaryDependencies(const std::string &path) {
        std::vector<std::string> dependencies;
        std::string output;

        // Get dependencies
        try {
            output = executeCommand("otool", {"-L", path});
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to get dependencies: " + std::string(e.what()));
        }

        static const std::regex depRegex(
            R"(^\t(.+) \(compatibility version (\d+\.\d+\.\d+), current version (\d+\.\d+\.\d+)(, weak)?\)$)");
        std::istringstream iss(output);
        std::string line;
        std::smatch match;

        // skip first line
        std::getline(iss, line);

        const std::string &loaderPath = path;
        while (std::getline(iss, line)) {
            if (std::regex_search(line, match, depRegex) && match.size() >= 2) {
                std::string dep = match[1].str();
                dependencies.emplace_back(dep);
            }
        }
        return dependencies;
    }

    std::vector<std::string>
        resolveUnixBinaryDependencies(const std::filesystem::path &path,
                                      const std::vector<std::filesystem::path> &searchingPaths,
                                      std::vector<std::string> *unparsed) {
        auto rpaths = readMacBinaryRPaths(path);
        for (const auto &item : searchingPaths) {
            rpaths.push_back(item);
        }

        auto dependencies = readMacBinaryDependencies(path);
        const std::string &loaderPath = fs::canonical(path).parent_path();

        std::vector<std::string> res;
        for (auto dep : std::as_const(dependencies)) {
            // Replace @executable_path and @loader_path
            replaceString(dep, std::string("@executable_path"), loaderPath);
            replaceString(dep, std::string("@loader_path"), loaderPath);

            // Find dependency
            std::string target = dep;
            if (dep.find("@rpath") != std::string::npos) {
                for (auto rpath : rpaths) {
                    // Replace again
                    replaceString(rpath, std::string("@executable_path"), loaderPath);
                    replaceString(rpath, std::string("@loader_path"), loaderPath);

                    std::string fullPath = dep;
                    replaceString(fullPath, std::string("@rpath"), rpath);
                    if (fs::exists(fullPath)) {
                        target = fullPath;
                        break;
                    }
                }
            }

            target = cleanPath(target);
            if (fs::exists(target)) {
                if (fs::canonical(target).filename() == fs::canonical(path).filename())
                    continue;
                res.push_back(target);
            } else if (unparsed) {
                unparsed->push_back(target);
            }
        }

        return res;
    }

    void setFileRPaths(const std::string &file, const std::vector<std::string> &paths) {
        // Remove rpaths
        do {
            auto rpaths = readMacBinaryRPaths(file);
            if (rpaths.empty())
                break;
            std::vector<std::string> args;
            args.reserve(rpaths.size() * 2 + 1);
            for (const auto &rpath : std::as_const(rpaths)) {
                args.push_back("-delete_rpath");
                args.push_back(rpath);
            }
            args.push_back(file);

            try {
                std::ignore = executeCommand("install_name_tool", args);
            } catch (const std::exception &e) {
                throw std::runtime_error("Failed to remove rpaths: " + std::string(e.what()));
            }
        } while (false);

        // Add rpaths
        if (!paths.empty()) {
            std::set<std::string> visited;
            std::vector<std::string> args;
            args.reserve(paths.size() * 2 + 1);
            for (const auto &rpath : std::as_const(paths)) {
                if (Utils::contains(visited, rpath))
                    continue;

                visited.insert(rpath);
                args.push_back("-add_rpath");
                args.push_back(rpath);
            }
            args.push_back(file);

            try {
                std::ignore = executeCommand("install_name_tool", args);
            } catch (const std::exception &e) {
                throw std::runtime_error("Failed to add rpaths: " + std::string(e.what()));
            }
        }
    }

    std::vector<std::string> getMacAbsoluteDependencies(const std::string &file) {
        auto deps = readMacBinaryDependencies(file);
        std::vector<std::string> res;
        for (const auto &dep : std::as_const(deps)) {
            if (fs::path(dep).is_absolute()) {
                res.push_back(dep);
            }
        }
        return res;
    }

    void replaceMacFileDependencies(
        const std::string &file, const std::vector<std::pair<std::string, std::string>> &depPairs) {
        std::string output;
        std::vector<std::string> args;
        args.reserve(depPairs.size() * 3 + 1);

        std::string id;
        for (const auto &pair : depPairs) {
            if (fs::exists(pair.first) &&
                fs::canonical(pair.first).filename() == fs::canonical(file).filename()) {
                id = pair.second;
                continue;
            }
            args.push_back("-change");
            args.push_back(pair.first);
            args.push_back(pair.second);
        }
        if (!id.empty()) {
            args.push_back("-id");
            args.push_back(id);
        }
        args.push_back(file);

        try {
            output = executeCommand("install_name_tool", args);
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to replace dependency: " + std::string(e.what()));
        }
    }

#else
    // Linux
    // Use `ldd` and `patchelf`

    static std::vector<std::string>
        readLddOutput(const std::string &fileName,
                      const std::vector<std::filesystem::path> &searchingPaths,
                      std::vector<std::string> *unparsed) {
        std::string output;

        try {
            output = executeCommand("ldd", {fileName});
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to get dependencies: " + std::string(e.what()));
        }

        std::istringstream iss(output);
        std::string line;

        static const std::regex regexp("^\\s*.+ => (.+) \\(.*");
        static const std::regex regexp2("^\\s*(.+) => not found");

        std::vector<std::string> dependencies;
        while (std::getline(iss, line)) {
            std::smatch match;
            if (std::regex_match(line, match, regexp) && match.size() >= 2) {
                dependencies.push_back(cleanPath(match[1].str()));
            } else if (std::regex_match(line, match, regexp2) && match.size() >= 2) {
                // Search in search paths
                fs::path target;
                for (const auto &item : searchingPaths) {
                    auto fullPath = item / match[1].str();
                    if (fs::exists(fullPath)) {
                        target = fullPath;
                        break;
                    }
                }

                if (!target.empty()) {
                    dependencies.push_back(target);
                } else {
                    unparsed->push_back(cleanPath(match[1].str()));
                }
            }
        }

        return dependencies;
    }

    std::vector<std::string>
        resolveUnixBinaryDependencies(const std::filesystem::path &path,
                                      const std::vector<std::filesystem::path> &searchingPaths,
                                      std::vector<std::string> *unparsed) {
        return readLddOutput(path, searchingPaths, unparsed);
    }

    void setFileRPaths(const std::string &file, const std::vector<std::string> &paths) {
        if (paths.empty()) {
            try {
                std::ignore = executeCommand("patchelf", {
                                                             "--remove-rpath",
                                                             file,
                                                         });
            } catch (const std::exception &e) {
                throw std::runtime_error("Failed to remove rpaths: " + std::string(e.what()));
            }
            return;
        }

        try {
            std::ignore = executeCommand("patchelf", {
                                                         "--set-rpath",
                                                         join(paths, std::string(":")),
                                                         file,
                                                     });
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to replace rpaths: " + std::string(e.what()));
        }
    }

#endif


#ifdef __linux__
    static inline bool errorIsInterpNotFound(const std::string &what) {
        return what.find("cannot find section '.interp'") != std::string::npos;
    };

    std::string getInterpreter(const std::string &file) {
        std::string output;
        try {
            output = executeCommand("patchelf", {
                                                    "--print-interpreter",
                                                    file,
                                                });
        } catch (const std::exception &e) {
            if (errorIsInterpNotFound(e.what()))
                return {};
            throw std::runtime_error("Failed to get interpreter: " + std::string(e.what()));
        }

        output = trim(output);
        replaceString(output, std::string("$ORIGIN"), fs::canonical(file).parent_path().string());
        return output;
    }

    bool setFileInterpreter(const std::string &file, const std::string &interpreter) {
        try {
            std::ignore = executeCommand("patchelf", {
                                                         "--set-interpreter",
                                                         interpreter,
                                                         file,
                                                     });
        } catch (const std::exception &e) {
            if (errorIsInterpNotFound(e.what()))
                return false;
            throw std::runtime_error("Failed to set interpreter: " + std::string(e.what()));
        }
        return true;
    }
#endif

}
