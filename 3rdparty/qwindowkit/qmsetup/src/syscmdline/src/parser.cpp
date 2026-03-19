#include "parser.h"
#include "parser_p.h"

#include <cctype>
#include <algorithm>

#ifdef SYSCMDLINE_ENABLE_VALIDITY_CHECK

#  include <stdexcept>

#endif

#include "utils_p.h"
#include "command_p.h"
#include "option_p.h"
#include "parseresult_p.h"

namespace SysCmdLine {

    namespace Strings::en_US {

        static const char *error_strings[] = {
            R"(No error.)",
            R"(Unknown option "%1".)",
            R"(Unknown command or argument "%1".)",
            R"(Missing required argument "%1" of option "%2".)",
            R"(Missing required argument "%1".)",
            R"(Too many arguments.)",
            R"(Invalid value "%1" of argument "%2".)",
            R"(Invalid occurrence of option "%1", which should be argument "%2".)",
            R"(Missing required option "%1".)",
            R"(Option "%1" occurs too much, at most %2.)",
            R"(Invalid token "%1" of argument "%2", expect "%3".)",
            R"(Invalid token "%1" of argument "%2", reason: %3)",
            R"(Options "%1" and "%2" are mutually exclusive.)",
            R"(Option "%1" and other arguments cannot be specified simultaneously.)",
            R"(Option "%1" and other options cannot be specified simultaneously.)",
        };

        static const char *title_strings[] = {
            "Error",    "Usage",    "Description", "Arguments", "Options",
            "Commands", "Required", "Default",     "Expected",
        };

        static const char *command_strings[] = {
            "", "Debug mode", "Show verbose", "Show version information", "Show help information",
        };

        static const char *info_strings[] = {
            R"("%1" is not matched. Do you mean one of the following?)",
        };

        static const char *token_strings[] = {
            "command",
            "options",
        };

        static const char **strings[] = {
            error_strings, title_strings, command_strings, info_strings, token_strings,
        };

        static std::string provider(int category, int index) {
            return strings[category][index];
        }

    }

    ParserPrivate::ParserPrivate()
        : displayOptions(Parser::Normal), textProvider(Strings::en_US::provider) {
    }

    ParserPrivate *ParserPrivate::clone() const {
        return new ParserPrivate(*this);
    }

    Parser::Parser() : SharedBase(new ParserPrivate()) {
    }

    Parser::Parser(const Command &rootCommand) : Parser() {
        setRootCommand(rootCommand);
    }

    std::string Parser::prologue() const {
        Q_D2(Parser);
        return d->prologue;
    }

    void Parser::setPrologue(const std::string &prologue) {
        Q_D(Parser);
        d->prologue = prologue;
    }

    std::string Parser::epilogue() const {
        Q_D2(Parser);
        return d->epilogue;
    }

    void Parser::setEpilogue(const std::string &epilogue) {
        Q_D(Parser);
        d->epilogue = epilogue;
    }

    int Parser::displayOptions() const {
        Q_D2(Parser);
        return d->displayOptions;
    }

    void Parser::setDisplayOptions(int displayOptions) {
        Q_D(Parser);
        d->displayOptions = displayOptions;
    }

    Command Parser::rootCommand() const {
        Q_D2(Parser);
        return d->rootCommand;
    }

    void Parser::setRootCommand(const Command &rootCommand) {
        Q_D(Parser);
#ifdef SYSCMDLINE_ENABLE_VALIDITY_CHECK
        if (rootCommand.name().empty()) {
            throw std::runtime_error("command doesn't have a name");
        }
#endif
        d->rootCommand = rootCommand;
    }

    namespace {

        class ParserCore {
        public:
            ParserCore(const std::vector<std::string> &params, int parseOptions, int displayOptions,
                       const Command *rootCommand)
                : params(params), parseOptions(parseOptions), displayOptions(displayOptions),
                  rootCommand(rootCommand), result(new ParseResultPrivate()), core(result->core) {
            }

            ~ParserCore() {
                delete[] optionRanges;
                core.allOptionTokenIndexes = std::move(allOptionTokenIndexes);
            }

            bool parse() {
                searchTargetCommandAndBuildIndexes();
                extractOptionsAndArguments();
                if (result->error != ParseResult::NoError) {
                    return false;
                }
                parseArguments();
                if (result->error != ParseResult::NoError) {
                    return false;
                }

                // Scan roles
                for (int i = 0; i < core.allOptionsSize; ++i) {
                    const auto &resultData = core.allOptionsResult[i];
                    if (resultData.count > 0) {
                        auto role = resultData.option->role();
                        if (role != Option::NoRole) {
                            result->roleSet[role] = true;
                        }
                    }
                }
                return true;
            }

            void searchTargetCommandAndBuildIndexes() {
                int globalOptionCount = 0;

                // 1. Find target command
                {
                    auto cmd = rootCommand;
                    size_t i = 1;
                    for (; i < params.size(); ++i) {
                        const auto &dd = cmd->d_func();
                        const auto &param = params[i];

                        size_t j = 0;
                        size_t size = dd->commands.size();
                        for (; j < size; ++j) {
                            const auto &name = dd->commands[j].name();
                            if (name == param || ((parseOptions & Parser::IgnoreCommandCase) &&
                                                  Utils::toLower(name) == Utils::toLower(param))) {
                                break;
                            }
                        }

                        if (j == size) {
                            break;
                        }

                        result->stack.push_back(int(j));
                        globalOptionCount += [](const Command *cmd) {
                            int cnt = 0;
                            for (const auto &opt : cmd->d_func()->options)
                                if (opt.isGlobal())
                                    cnt++;
                            return cnt;
                        }(cmd);
                        cmd = &cmd->d_func()->commands.at(j);
                    }
                    nonCommandIndex = i;
                    result->command = cmd;
                    targetCommandData = cmd->d_func();

                    // Build command indexes
                    for (size_t j = 0; j < targetCommandData->commands.size(); ++j) {
                        core.cmdNameIndexes[targetCommandData->commands[j].name()] = ele(int(j));
                    }
                }

                // 2. Collect options along the command path
                const auto **globalOptionList = new const Option *[globalOptionCount]; // Alloc
                {
                    int globalOptionListIndex = 0;
                    auto cmd = rootCommand;
                    for (size_t i = 0; i < result->stack.size(); ++i) {
                        const auto &d = cmd->d_func();

                        // Add options
                        for (const auto &option : d->options) {
                            if (!option.isGlobal())
                                continue;
                            globalOptionList[globalOptionListIndex++] = &option;
                        }
                        cmd = &d->commands[i];
                    }
                }

                // 3. Remove duplicated options from end to begin
                int realGlobalOptionCount = globalOptionCount;
                {
                    GenericMap visitedTokens;
                    for (int i = globalOptionCount - 1; i >= 0; --i) {
                        auto &opt = globalOptionList[i];
                        const auto &dd = opt->d_func();

                        bool visited = false;
                        for (const auto &token : dd->tokens) {
                            if (Utils::contains(visitedTokens, token)) {
                                visited = true;
                                break;
                            }
                        }

                        if (visited) {
                            realGlobalOptionCount--;
                            opt = nullptr; // mark invalid
                            continue;
                        }

                        for (const auto &token : dd->tokens) {
                            visitedTokens[token] = ele(size_t(0));
                        }
                    }
                }

                // 4. Alloc option spaces
                {
                    core.allOptionsSize =
                        realGlobalOptionCount + int(targetCommandData->options.size());
                    core.globalOptionsSize = realGlobalOptionCount;
                    core.allOptionsResult = new OptionData[core.allOptionsSize];

                    // init options
                    int allOptionsIndex = 0;
                    for (int i = 0; i < globalOptionCount; ++i) {
                        auto opt = globalOptionList[i];
                        if (!opt)
                            continue;
                        initOptionData(core.allOptionsResult[allOptionsIndex++], opt);
                    }

                    for (const auto &option : targetCommandData->options) {
                        initOptionData(core.allOptionsResult[allOptionsIndex++], &option);
                    }
                }

                delete[] globalOptionList; // Free

                // 5. Alloc command argument space
                {
                    initArgumentHolderData(core, targetCommandData->arguments);
                    core.argResult = new std::vector<Value>[core.argSize];
                    for (int i = 0; i < core.argSize; ++i) {
                        core.argResult[i].reserve(1); // most are single-value argument
                    }
                }

                // 6. Build option indexes
                buildOptionTokenIndexes(allOptionTokenIndexes,
                                        [](const std::string &s) { return s; });

                // Build case-insensitive option indexes if needed
                if ((parseOptions & Parser::IgnoreOptionCase)) {
                    buildOptionTokenIndexes(lowerOptionTokenIndexes, [](const std::string &s) {
                        return Utils::toLower(s); //
                    });
                }
            }

            void extractOptionsAndArguments() {
                optionRanges = new OptionRange[core.allOptionsSize]; // Alloc

                struct TokenOptionResult {
                    int optIndex;
                    int pos;
                };

                enum TokenResultType {
                    TRT_Nothing,
                    TRT_Option,
                    TRT_GroupFlags,
                };

                TokenOptionResult optionResult;
                std::vector<int> groupFlagsResult;
                TokenResultType resultType = TRT_Nothing;

                const auto &tryOption = [&optionResult, this](const std::string &token) {
                    return (optionResult.optIndex = searchOption(token, &optionResult.pos)) >= 0;
                };

                const auto &tryGroupFlags = [&groupFlagsResult, this](const std::string &token) {
                    return (parseOptions & Parser::AllowUnixGroupFlags) && isFlags(token) &&
                           !(groupFlagsResult = searchGroupFlags(token)).empty();
                };

                for (auto i = nonCommandIndex; i < params.size(); ++i) {
                    const auto &token = params[i];
                    auto lastResultType = resultType;
                    resultType = TRT_Nothing;

                    // Consider option
                    if (lastResultType == TRT_Option || tryOption(token)) {
                        auto optIndex = optionResult.optIndex;
                        auto pos = optionResult.pos;

                        const auto &optData = core.allOptionsResult[optIndex];
                        const auto &opt = optData.option;
                        auto &rangeData = optionRanges[optIndex];

                        // Check option common
                        if (!checkOptionCommon(token, optIndex, rangeData.size())) {
                            break;
                        }

                        const auto &dd = opt->d_func();

                        // Collect positional arguments
                        if (pos >= 0) {
                            // Must be a single value option
                            rangeData.push(int(i), 0, token.substr(pos));
                        } else if (!dd->arguments.empty()) {
                            int minArgCount = (optData.optionalArgIndex < 0)
                                                  ? int(dd->arguments.size())
                                                  : optData.optionalArgIndex;
                            int maxArgCount = (optData.multiValueArgIndex < 0)
                                                  ? (minArgCount + 1 + optData.optionalArgIndex)
                                                  : 65535;

                            auto j = i + minArgCount + 1; // next of last required index
                            if (j > params.size()) {
                                size_t argIndex = params.size() - i - 1;
                                buildError(ParseResult::MissingOptionArgument,
                                           {
                                               dd->arguments[argIndex].helpText(
                                                   Symbol::HP_ErrorText, displayOptions),
                                               opt->helpText(Symbol::HP_ErrorText, displayOptions),
                                           },
                                           {}, nullptr, opt);
                                break;
                            }

                            bool hasRemainder =
                                optData.multiValueArgIndex >= 0 &&
                                dd->arguments[optData.multiValueArgIndex].number() ==
                                    Argument::Remainder;
                            auto end = std::min(params.size(), i + maxArgCount + 1);
                            for (int argIndex = minArgCount; j < end; ++j, ++argIndex) {
                                if (hasRemainder && argIndex >= optData.multiValueArgIndex) {
                                    j = end;
                                    break;
                                }

                                const auto &curToken = params[j];

                                // Break at next option
                                if (tryOption(curToken)) {
                                    resultType = TRT_Option; // memorize last result
                                    break;
                                }

                                // Break at next group flags
                                if (tryGroupFlags(curToken)) {
                                    resultType = TRT_GroupFlags; // memorize last result
                                    break;
                                }
                            }

                            rangeData.push(int(i), int(j - i - 1));
                            i = j - 1;
                        } else {
                            rangeData.push(int(i), 0);
                        }

                        if (opt->priorLevel() >
                            (priorOpt ? priorOpt->priorLevel() : Option::NoPrior)) {
                            priorOpt = opt;
                        }

                        hasOption = true;
                        continue;
                    }

                    // Consider group flags
                    if (lastResultType == TRT_GroupFlags || tryGroupFlags(token)) {
                        const auto &flags = groupFlagsResult;
                        bool failed = false;
                        for (const auto &optIdx : std::as_const(flags)) {
                            auto &rangeData = optionRanges[optIdx];

                            // Check option common
                            if (!checkOptionCommon(token, optIdx, rangeData.size())) {
                                failed = true;
                                break;
                            }

                            rangeData.push(int(i), 0);
                        }

                        if (failed) {
                            break;
                        }
                        hasOption = true;
                        continue;
                    }

                    // Consider argument
                    positionalArguments.push_back(token);
                }

                if (!positionalArguments.empty()) {
                    hasArgument = true;
                }
            }

            void parseArguments() {
                // Parse all options
                bool failed = false;
                for (int i = 0; i < core.allOptionsSize; ++i) {
                    auto &resultData = core.allOptionsResult[i];
                    const auto &args = resultData.option->d_func()->arguments;
                    const auto &rangeData = optionRanges[i];
                    const auto &occurrence = int(rangeData.starts.size());

                    resultData.count = occurrence;
                    resultData.argResult = new std::vector<Value> *[occurrence];
                    for (int j = 0; j < occurrence; ++j) {
                        resultData.argResult[j] = new std::vector<Value>[resultData.argSize];
                        for (int k = 0; k < resultData.argSize; ++k) {
                            resultData.argResult[j][k].reserve(1); // most are single-value argument
                        }
                    }

                    for (int j = 0; j < occurrence; ++j) {
                        auto &resVec = resultData.argResult[j];

                        const auto &start = rangeData.starts[j];
                        const auto &len = rangeData.lengths[j];
                        const auto &preceding = rangeData.precedingTokens[j];
                        if (len == 0) {
                            if (!preceding.empty()) {
                                // single argument option
                                resVec[0].emplace_back(preceding);
                            }
                            continue;
                        }

                        // missing index must be -1
                        // because we have already check the integrity
                        std::ignore =
                            parsePositionalArguments(args, params.data() + start + 1, len, resVec,
                                                     resultData.multiValueArgIndex);
                        if (result->error != ParseResult::NoError) {
                            failed = true;
                            break;
                        }
                    }

                    if (failed) {
                        break;
                    }
                }

                // Parse positional arguments
                auto missingIdx = parsePositionalArguments(
                    targetCommandData->arguments, positionalArguments.data(),
                    positionalArguments.size(), core.argResult, core.multiValueArgIndex);
                if (result->error != ParseResult::NoError) {
                    return;
                }

                bool hasAutoOption = false;

                // Automatic set options
                if (!hasOption && !hasArgument) {
                    for (int i = 0; i < core.allOptionsSize; ++i) {
                        auto &optionData = core.allOptionsResult[i];
                        const auto &opt = *optionData.option;
                        if (opt.priorLevel() == Option::AutoSetWhenNoSymbols) {
                            optionData.count = 1;

                            // new
                            auto &resultData = optionData.argResult;
                            resultData = new std::vector<Value> *[1];
                            resultData[0] = new std::vector<Value>[0]; // alloc empty

                            hasAutoOption = true;
                            break;
                        }
                    }
                }

                bool canIgnoreArgumnents = priorOpt != nullptr;
                bool canIgnoreSymbols =
                    priorOpt && priorOpt->priorLevel() >= Option::IgnoreMissingSymbols;
                if (canIgnoreSymbols || hasAutoOption) {
                    // ...
                } else if (!canIgnoreArgumnents && missingIdx >= 0) {
                    // Required arguments
                    const auto &arg = targetCommandData->arguments[missingIdx];
                    buildError(ParseResult::MissingCommandArgument,
                               {
                                   arg.helpText(Symbol::HP_ErrorText, displayOptions),
                               },
                               {}, &arg);
                } else {
                    // Required options
                    const Option *missingOpt = nullptr;
                    for (int i = 0; i < core.allOptionsSize; ++i) {
                        const auto &opt = *core.allOptionsResult[i].option;
                        if (opt.isRequired() && searchExclusiveOption(i) < 0 &&
                            core.allOptionsResult[i].count == 0) {
                            missingOpt = &opt;
                            break;
                        }
                    }

                    if (missingOpt) {
                        buildError(ParseResult::MissingRequiredOption,
                                   {
                                       missingOpt->helpText(Symbol::HP_ErrorText, displayOptions),
                                   },
                                   {}, nullptr, missingOpt);
                    }
                }
            }

            const std::vector<std::string> &params;
            const int parseOptions;
            const int displayOptions;
            const Command *const rootCommand;

            ParseResultPrivate *result;
            ParseResultData2 &core;
            size_t nonCommandIndex = 1;
            const CommandPrivate *targetCommandData = nullptr; // for convenience
            bool hasArgument = false;
            bool hasOption = false;
            const Option *priorOpt = nullptr;

            GenericMap allOptionTokenIndexes;
            GenericMap lowerOptionTokenIndexes;
            GenericMap encounteredExclusiveGroups;

            struct OptionRange {
                std::vector<int> starts;
                std::vector<int> lengths;
                std::vector<std::string> precedingTokens;

                void push(int s, int l, std::string preceding = {}) {
                    starts.push_back(s);
                    lengths.push_back(l);
                    precedingTokens.emplace_back(std::move(preceding));
                }

                inline int size() const {
                    return int(starts.size());
                }
            };

            OptionRange *optionRanges = nullptr;
            std::vector<std::string> positionalArguments;

            // Reusable functions
            void buildOptionTokenIndexes(GenericMap &indexes,
                                         std::string (*f)(const std::string &)) const {
                for (int i = 0; i < core.allOptionsSize; ++i) {
                    const auto &opt = core.allOptionsResult[i].option;
                    for (const auto &token : opt->d_func()->tokens) {
                        indexes[f(token)] = ele(i);
                    }
                }
            }

            static inline void initOptionData(OptionData &data, const Option *option) {
                data.option = option;
                initArgumentHolderData(data, option->d_func()->arguments);
            }

            static void initArgumentHolderData(ArgumentHolderData &data,
                                               const std::vector<Argument> &args) {
                data.argSize = int(args.size());

                // Build arg name indexes
                for (int i = 0; i < args.size(); ++i) {
                    const auto &arg = args[i];
                    if (arg.isOptional() && data.optionalArgIndex < 0) {
                        data.optionalArgIndex = i;
                    }
                    if (arg.multiValueEnabled() && data.multiValueArgIndex < 0) {
                        data.multiValueArgIndex = i;
                    }
                    data.argNameIndexes[arg.name()] = ele(i);
                }
            };

            // indexes: token indexes map
            // token:   token
            // pos:     followed argument beginning index
            // ->       option index
            int searchOptionImpl(const GenericMap &indexes, const std::string &token,
                                 int *pos) const {
                if (pos)
                    *pos = -1;

                if (indexes.empty())
                    return -1;

                // Find the first element greater or equal than given token
                auto it = indexes.lower_bound(token);

                // A.
                // For example,
                // token = -l
                // indexes = ..., -l, -m, -n
                // then `it` points to `-l`
                if (it != indexes.end() && it->first == token) {
                    return it->second.i; // The luckiest situation
                }

                // Only Unix or Dos option can fallback to short match
                auto front = token.front();
                if (front != '-' && front != '/') {
                    return -1;
                }

                // B.
                // Another example,
                // token = -lpthread
                // indexes = ..., -m, -n
                // then `it` points to `-m`

                // In such case, we should try short option

                // B.A. If all elements are greater than the given token, abort
                if (it == indexes.begin()) {
                    return -1;
                }

                // B.B. The predecessor maybe the target
                it--;
                const auto &prefix = it->first;

                // B.B.A.
                // For example,
                // token = -lpthread
                // indexes = -j, -k, -m, -n
                // then `it` points to -k, not match
                if (token.size() == 1 || !Utils::starts_with(token, prefix)) {
                    return -1;
                }

                // B.B.B.
                // Another example,
                // token = -lpthread
                // indexes = -j, -k, -l, -m, -n
                // then `it` points to -l, match

                char sign;
                if (front == '/') {
                    // Try dos short option
                    if ((parseOptions & Parser::AllowDosShortOptions)) {
                        sign = ':';
                        goto short_match;
                    }
                } else if (!(parseOptions & Parser::DontAllowUnixShortOptions)) {
                    // Try unix short option
                    // Ignore `--` option because it's too special
                    if (prefix != "--") {
                        sign = '=';
                        goto short_match;
                    }
                }
                return -1;

            short_match:
                const auto &idx = it->second.i;
                const auto &opt = core.allOptionsResult[idx].option;
                const auto &args = opt->d_func()->arguments;

                // only option with single required argument can be matched
                if (args.size() != 1 || !args.front().isRequired()) {
                    return -1;
                }

                switch (opt->shortMatchRule()) {
                    case Option::ShortMatchSingleLetter: {
                        if (!std::isalpha(prefix.at(1)))
                            break;
                    }
                    case Option::ShortMatchSingleChar: {
                        if (prefix.size() > 2)
                            break;
                    }
                    case Option::ShortMatchAll: {
                        if (pos)
                            *pos = int(prefix.size());
                        return idx;
                    }
                    default:
                        break;
                }

                if (token.at(prefix.size()) == sign) {
                    if (pos)
                        *pos = int(prefix.size()) + 1;
                    return idx;
                }
                return -1;
            };

            // token:   token
            // pos:     followed argument beginning index
            // ->       option index
            int searchOption(const std::string &token, int *pos = nullptr) const {
                if (auto ch = token.front(); ch != '-' && ch != '/') {
                    return -1;
                }

                // first search case-sensitive map
                if (auto idx = searchOptionImpl(allOptionTokenIndexes, token, pos); idx >= 0)
                    return idx;

                // second search case-insensitive map if flag is set
                if ((parseOptions & Parser::IgnoreOptionCase)) {
                    return searchOptionImpl(lowerOptionTokenIndexes, Utils::toLower(token), pos);
                }
                return -1;
            };

            // flags: group flags without preceding '-'
            // ->     option indexes
            std::vector<int> searchGroupFlags(const std::string &flags) const {
                std::vector<int> res;
                char token[] = {'-', '-', '\0'};
                for (size_t i = 1; i < flags.size(); ++i) {
                    token[1] = flags[i];

                    // Must be all of flags
                    auto it = allOptionTokenIndexes.find(token);
                    if (it == allOptionTokenIndexes.end()) {
                        return {};
                    }
                    const auto &idx = it->second.i;
                    const auto &opt = core.allOptionsResult[idx].option;
                    if (!opt->d_func()->arguments.empty()) {
                        return {};
                    }
                    res.push_back(idx);
                }
                return res;
            };

            void buildError(ParseResult::Error error, const std::vector<std::string> &placeholders,
                            const std::string &cancellationToken, const Argument *arg,
                            const Option *opt = nullptr) const {
                auto &res = *result;
                res.error = error;
                res.errorPlaceholders = placeholders;
                res.cancellationToken = cancellationToken;
                res.errorArgument = arg;
                res.errorOption = opt;
            };

            // arg:       input argument
            // token:     token
            // val:       return value if success
            // setError:  whether to build error message if failed
            bool checkArgument(const Argument *arg, const std::string &token, Value *out,
                               bool setError = true) const {
                const auto &d = arg->d_func();
                const auto &expectedValues = d->expectedValues;
                if (!expectedValues.empty()) {
                    for (const auto &item : expectedValues) {
                        auto val = Value::fromString(token, item.type());
                        if (val == item) {
                            *out = val;
                            return true;
                        }
                    }
                    if (setError) {
                        if (token.front() == '-') {
                            buildError(ParseResult::InvalidOptionPosition, {token, arg->name()},
                                       token, arg);
                        } else {
                            buildError(ParseResult::InvalidArgumentValue, {token, arg->name()},
                                       token, arg);
                        }
                    }
                    return false;
                }

                if (d->validator) {
                    std::string errorMessage;
                    if (d->validator(token, out, &errorMessage)) {
                        return true;
                    }
                    if (setError) {
                        buildError(ParseResult::ArgumentValidateFailed,
                                   {token, arg->name(), errorMessage}, token, arg);
                    }
                    return false;
                }

                const auto &type = d->defaultValue.type();
                if (type == Value::Null) {
                    *out = token; // no default value
                    return true;
                }
                if (auto val = Value::fromString(token, type); val.type() != Value::Null) {
                    *out = val;
                    return true;
                }
                if (setError) {
                    buildError(ParseResult::ArgumentTypeMismatch,
                               {
                                   token,
                                   arg->name(),
                                   Value::typeName(type),
                               },
                               token, arg);
                }
                return false;
            };

            // optIndex:         option index of all option list
            // insertIfNotFound: if not colliding, set current group as visited
            // ->                colliding option index in command's option list
            int searchExclusiveOption(int optIndex, bool insertIfNotFound = false) {
                if (optIndex < core.globalOptionsSize)
                    return -1;
                optIndex -= core.globalOptionsSize; // get index in command's option list

                const auto &groupName = targetCommandData->optionGroupNames[optIndex];
                if (groupName.empty())
                    return -1;

                auto it2 = encounteredExclusiveGroups.find(groupName);
                if (it2 != encounteredExclusiveGroups.end()) {
                    return it2->second.i; // colliding
                }

                if (insertIfNotFound) {
                    encounteredExclusiveGroups[groupName] = ele(optIndex);
                }
                return -1;
            };

            bool checkOptionCommon(const std::string &token, int optIndex, int occurrence) {
                const auto &opt = core.allOptionsResult[optIndex].option;
                // Check max occurrence
                if (opt->maxOccurrence() > 0 && occurrence == opt->maxOccurrence()) {
                    buildError(ParseResult::OptionOccurTooMuch,
                               {
                                   opt->helpText(Symbol::HP_ErrorText, displayOptions),
                                   std::to_string(opt->maxOccurrence()),
                               },
                               token, nullptr, opt);
                    return false;
                }

                // Check priority
                if (priorOpt) {
                    switch (priorOpt->priorLevel()) {
                        case Option::ExclusiveToArguments: {
                            if (hasArgument) {
                                buildError(
                                    ParseResult::PriorOptionWithArguments,
                                    {
                                        priorOpt->helpText(Symbol::HP_ErrorText, displayOptions),
                                    },
                                    token, nullptr, opt);
                            }
                            break;
                        }
                        case Option::ExclusiveToOptions: {
                            if (hasOption) {
                                buildError(
                                    ParseResult::PriorOptionWithOptions,
                                    {
                                        priorOpt->helpText(Symbol::HP_ErrorText, displayOptions),
                                    },
                                    token, nullptr, opt);
                            }
                            break;
                        }
                        case Option::ExclusiveToAll: {
                            if (hasArgument) {
                                buildError(
                                    ParseResult::PriorOptionWithArguments,
                                    {
                                        priorOpt->helpText(Symbol::HP_ErrorText, displayOptions),
                                    },
                                    token, nullptr, opt);
                            } else if (hasOption) {
                                buildError(
                                    ParseResult::PriorOptionWithOptions,
                                    {
                                        priorOpt->helpText(Symbol::HP_ErrorText, displayOptions),
                                    },
                                    token, nullptr, opt);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }

                // Check exclusive
                {
                    const auto &exclusiveIdx = searchExclusiveOption(optIndex, true);
                    if (exclusiveIdx >= 0) {
                        buildError(ParseResult::MutuallyExclusiveOptions,
                                   {
                                       core.allOptionsResult[core.globalOptionsSize + exclusiveIdx]
                                           .option->helpText(Symbol::HP_ErrorText, displayOptions),
                                       opt->helpText(Symbol::HP_ErrorText, displayOptions),
                                   },
                                   token, nullptr, opt);
                        return false;
                    }
                }
                return true;
            };

            static bool isFlags(const std::string &s) {
                if (s.size() <= 1 || s.front() != '-')
                    return false;
                return std::all_of(s.begin() + 1, s.end(), ::isalnum);
            }

            static bool isSymbol(std::string_view s) {
                if (!::isalpha(s.front()))
                    return false;
                return std::all_of(s.begin() + 1, s.end(), [](char ch) {
                    return ::isalnum(ch) || ch == '_'; //
                });
            }

            // args:    arguments
            // tokens:  tokens
            // res:     result array
            // ->       missing index
            // if failed, the error will be set, check it first.
            int parsePositionalArguments(const std::vector<Argument> &args,
                                         const std::string *tokens, size_t tokensCount,
                                         std::vector<Value> *res, int multiValueIndex) const {
                // Parse forward
                size_t end = args.size();
                if (multiValueIndex >= 0) {
                    end = multiValueIndex + 1; // Stop after multi-value arg
                }

                size_t k = 0;
                for (size_t max = std::min(tokensCount, end); k < max; ++k) {
                    const auto &arg = args.at(k);
                    Value val;
                    if (!checkArgument(&arg, tokens[k], &val)) {
                        return -1;
                    }
                    res[k].push_back(val);
                }

                if (k < end) {
                    const auto &arg = args.at(k);
                    if (arg.isRequired()) {
                        return int(k);
                    }
                    return -1;
                }

                // Parse backward
                end = tokensCount;
                if (multiValueIndex >= 0 && multiValueIndex < args.size() - 1) {
                    size_t backwardCount = args.size() - multiValueIndex - 1;
                    if (tokensCount < backwardCount + k) {
                        return multiValueIndex + 1;
                    }
                    end -= backwardCount;

                    for (size_t j = 0; j < backwardCount; ++j) {
                        const auto &arg = args.at(multiValueIndex + j + 1);
                        Value val;
                        if (!checkArgument(&arg, tokens[end + j], &val)) {
                            return -1;
                        }
                        res[multiValueIndex + j + 1].push_back(val);
                    }
                }

                if (end <= k) {
                    return -1;
                }

                // Too many
                if (multiValueIndex < 0) {
                    const auto &token = tokens[k];
                    if (token.front() == '-') {
                        buildError(ParseResult::UnknownOption, {token}, token, nullptr);
                        return -1;
                    }

                    if (args.empty() && isSymbol(token)) {
                        buildError(ParseResult::UnknownCommand, {token}, token, nullptr);
                        return -1;
                    }

                    buildError(ParseResult::TooManyArguments, {}, token, nullptr);
                    return -1;
                }

                // Consider multiple arguments
                const auto &arg = args.at(multiValueIndex);
                auto &resVec = res[multiValueIndex];
                for (size_t j = k; j < end; ++j) {
                    const auto &token = tokens[j];
                    Value val;
                    if (!checkArgument(&arg, token, &val)) {
                        break;
                    }
                    resVec.push_back(val);
                }
                return -1;
            };
        };

    }

    ParseResult Parser::parse(const std::vector<std::string> &args, int parseOptions) {
        Q_D2(Parser);
        ParserCore parserCore(args, parseOptions, d->displayOptions, &d->rootCommand);
        std::ignore = parserCore.parse();

        auto res = parserCore.result;
        res->arguments = args;
        res->parser = *this;
        return res;
    }

    int Parser::size(Parser::SizeType sizeType) const {
        Q_D2(Parser);
        return d->sizeConfig[sizeType];
    }

    void Parser::setSize(Parser::SizeType sizeType, int value) {
        Q_D(Parser);
        d->sizeConfig[sizeType] = value;
    }

    Parser::TextProvider Parser::textProvider() {
        Q_D2(Parser);
        return d->textProvider;
    }

    void Parser::setTextProvider(Parser::TextProvider textProvider) {
        Q_D(Parser);
        d->textProvider = textProvider;
    }

    Parser::TextProvider Parser::defaultTextProvider() {
        return Strings::en_US::provider;
    }

}