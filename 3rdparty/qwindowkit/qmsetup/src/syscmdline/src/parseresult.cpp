#include "parseresult.h"
#include "parseresult_p.h"

#include <algorithm>
#include <stdexcept>

#include "utils_p.h"
#include "strings.h"
#include "system.h"

#include "parser_p.h"
#include "option_p.h"
#include "helplayout_p.h"
#include "command_p.h"

namespace SysCmdLine {

    const OptionData &OptionData::sharedNull() {
        static OptionData _data;
        return _data;
    }

    static const std::vector<Value> &sharedEmptyValues() {
        static std::vector<Value> _data;
        return _data;
    }

    OptionResult::OptionResult() : data(&OptionData::sharedNull()) {
    }

    Option OptionResult::option() const {
        auto &v = *reinterpret_cast<const OptionData *>(data);
        return v.option ? *v.option : Option();
    }

    int OptionResult::indexOf(const std::string &name) const {
        auto &v = *reinterpret_cast<const OptionData *>(data);
        auto it = v.argNameIndexes.find(name);
        if (it == v.argNameIndexes.end())
            return -1;
        return it->second.i;
    }

    int OptionResult::count() const {
        auto &v = *reinterpret_cast<const OptionData *>(data);
        return v.count;
    }

    std::vector<Value> OptionResult::allValues(int index) const {
        auto &v = *reinterpret_cast<const OptionData *>(data);
        if (index < 0 || index >= v.argSize)
            return {};

        std::vector<Value> allValues;
        for (int i = 0; i < v.count; ++i) {
            const auto &values = v.argResult[i][index];
            // allValues.insert(allValues.end(), values.begin(), values.end());
            allValues = Utils::concatVector(allValues, values);
        }
        return allValues;
    }

    const std::vector<Value> &OptionResult::values(int index, int n) const {
        auto &v = *reinterpret_cast<const OptionData *>(data);
        if (index < 0 || index >= v.argSize)
            return sharedEmptyValues();
        if (n < 0 || n >= v.count)
            return sharedEmptyValues();
        return v.argResult[n][index];
    }

    Value OptionResult::value(int index, int n) const {
        auto &v = *reinterpret_cast<const OptionData *>(data);
        if (index < 0 || index >= v.argSize)
            return {};
        if (n < 0 || n >= v.count)
            return v.option->d_func()->arguments[index].defaultValue();
        const auto &args = v.argResult[n][index];
        return args.empty() ? Value() : args.front();
    }

    std::string ParseResultPrivate::correctionText() const {
        std::vector<std::string> expectedValues;
        switch (error) {
            case ParseResult::UnknownOption: {
                for (int i = 0; i < core.allOptionsSize; ++i) {
                    const auto &opt = *core.allOptionsResult[i].option;
                    for (const auto &token : opt.d_func()->tokens) {
                        expectedValues.push_back(token);
                    }
                }
                break;
            }

            case ParseResult::InvalidArgumentValue: {
                auto d = errorArgument->d_func();
                for (const auto &item : d->expectedValues) {
                    expectedValues.push_back(item.toString());
                }
                break;
            }

            case ParseResult::UnknownCommand: {
                for (const auto &cmd : command->d_func()->commands) {
                    expectedValues.push_back(cmd.name());
                }
                break;
            }

            default:
                return {};
        }

        auto input = errorPlaceholders[0];
        auto suggestions = Utils::calcClosestTexts(expectedValues, input, int(input.size()) / 2);
        if (suggestions.empty())
            return {};

        std::string ss;
        const auto &parserData = parser.d_func();
        ss += Utils::formatText(
            parserData->textProvider(Strings::Information, Strings::MatchCommand), {input});
        for (const auto &item : std::as_const(suggestions)) {
            ss += "\n" + parserData->indent() + item;
        }
        return ss;
    }

    std::vector<Option> ParseResultPrivate::globalOptions() const {
        std::vector<Option> res;
        res.reserve(core.globalOptionsSize);
        for (int i = 0; i < core.globalOptionsSize; ++i) {
            res.push_back(*core.allOptionsResult[i].option);
        }
        return res;
    }

    void ParseResultPrivate::showMessage(const std::string &info, const std::string &warn,
                                         const std::string &err, bool isMsg) const {
        // Make it as a POD structure
        struct Lists {
            HelpLayout::List *data;
            int size;
        };

        // Avoid using `std::function` to reduce binary size
        const auto &getLists = [](int displayOptions, const GenericMap &catalog,
                                  const StringList &catalogNames, // catalog

                                  const GenericMap &symbolIndexes, // name -> index
                                  int symbolCount, const Symbol *(*getter)(int, const void *),
                                  const void *user, // get symbol from index

                                  std::string (*getName)(const Symbol *), // get name of symbol
                                  int *maxWidth, void *extra,
                                  const std::string &defaultTitle) -> Lists {
            Lists res;
            int index = 0;
            res.data = new HelpLayout::List[catalogNames.size() + 1];

            // symbol indexes
            std::vector<int> visitedIndexes(symbolCount);

            // catalogues
            for (const auto &catalogName : catalogNames) {
                auto &list = res.data[index];
                list.title = catalogName;

                auto &symbolNames = *catalog.find(catalogName)->second.sl;
                bool empty = true;
                for (const auto &name : symbolNames) {
                    auto it = symbolIndexes.find(name);
                    if (it == symbolIndexes.end())
                        continue;

                    auto idx = it->second.i;
                    const auto &sym = getter(idx, user);
                    auto first = sym->helpText(Symbol::HP_FirstColumn, displayOptions, extra);
                    auto second = sym->helpText(Symbol::HP_SecondColumn, displayOptions, extra);
                    *maxWidth = std::max(int(first.size()), *maxWidth);
                    list.firstColumn.emplace_back(std::move(first));
                    list.secondColumn.emplace_back(std::move(second));
                    visitedIndexes[idx] = 1;
                    empty = false;
                }

                if (!empty)
                    index++; // index inc
            }

            // rest
            {
                auto &list = res.data[index];
                list.title = defaultTitle;

                bool empty = true;
                for (int i = 0; i < symbolCount; ++i) {
                    if (visitedIndexes[i])
                        continue;

                    const auto &sym = getter(i, user);
                    auto first = sym->helpText(Symbol::HP_FirstColumn, displayOptions, extra);
                    auto second = sym->helpText(Symbol::HP_SecondColumn, displayOptions, extra);
                    *maxWidth = std::max(int(first.size()), *maxWidth);
                    list.firstColumn.emplace_back(std::move(first));
                    list.secondColumn.emplace_back(std::move(second));
                    empty = false;
                }

                if (!empty)
                    index++; // index inc
            }

            res.size = index;
            return res;
        };

        const auto &d = command->d_func();
        const auto &parserData = parser.d_func();
        const auto &catalogueData = d->catalogue.d_func();
        const auto displayOptions = parserData->displayOptions;

        bool noHelp = isMsg && (displayOptions & Parser::DontShowHelpOnError);
        bool noIntro = isMsg && (displayOptions & Parser::DontShowIntroOnError);

        int maxWidth = 0;
        auto reorderedOptions = OptionPrivate::reorderOptions(d->options, globalOptions());

        // Alloc

        Lists argLists =
            noHelp ? Lists{nullptr, 0}
                   : getLists(
                         displayOptions, catalogueData->arg.data, catalogueData->arguments,
                         core.argNameIndexes, int(d->arguments.size()),
                         [](int i, const void *user) -> const Symbol * {
                             return &reinterpret_cast<decltype(d)>(user)->arguments[i]; //
                         },
                         d,
                         [](const Symbol *s) {
                             return static_cast<const Argument *>(s)->name(); //
                         },
                         &maxWidth, reinterpret_cast<void *>(parserData->textProvider),
                         parserData->textProvider(Strings::Title, Strings::Arguments));

        Lists optLists =
            noHelp
                ? Lists{nullptr, 0}
                : getLists(
                      displayOptions, catalogueData->opt.data, catalogueData->options,
                      core.allOptionTokenIndexes, int(core.allOptionsSize),
                      [](int i, const void *user) -> const Symbol * {
                          return &(*reinterpret_cast<const decltype(reorderedOptions) *>(user))[i];
                      },
                      &reorderedOptions,
                      [](const Symbol *s) {
                          return static_cast<const Option *>(s)->token(); //
                      },
                      &maxWidth, reinterpret_cast<void *>(parserData->textProvider),
                      parserData->textProvider(Strings::Title, Strings::Options));

        Lists cmdLists = noHelp
                             ? Lists{nullptr, 0}
                             : getLists(
                                   displayOptions, catalogueData->cmd.data, catalogueData->commands,
                                   core.cmdNameIndexes, int(d->commands.size()),
                                   [](int i, const void *user) -> const Symbol * {
                                       return &reinterpret_cast<decltype(d)>(user)->commands[i]; //
                                   },
                                   d,
                                   [](const Symbol *s) {
                                       return static_cast<const Command *>(s)->name(); //
                                   },
                                   &maxWidth, reinterpret_cast<void *>(parserData->textProvider),
                                   parserData->textProvider(Strings::Title, Strings::Commands));

        // Get valid help layout
        const HelpLayoutPrivate *helpLayoutData = nullptr;
        {
            int cmdCnt = stack.size() + 1;
            auto cmds = new const Command *[cmdCnt]; // alloc
            auto cmd = &parserData->rootCommand;
            cmds[0] = cmd;
            int cmdIdx = 0;
            for (const auto &idx : std::as_const(stack)) {
                cmd = &cmd->d_func()->commands[idx];
                cmds[++cmdIdx] = cmd;
            }
            for (int i = cmdCnt - 1; i >= 0; --i) {
                auto curHelpLayoutData = cmds[i]->d_func()->helpLayout.d_func();
                if (!curHelpLayoutData->itemDataList.empty()) {
                    helpLayoutData = curHelpLayoutData;
                    break;
                }
            }
            delete[] cmds; // free

            if (!helpLayoutData) {
                static HelpLayout defaultHelpLayout = HelpLayout::defaultHelpLayout();
                helpLayoutData = defaultHelpLayout.d_func();
            }
        }
        if ((displayOptions & Parser::AlignAllCatalogues)) {
            for (const auto &helpItem : helpLayoutData->itemDataList) {
                if (helpItem.itemType != HelpLayoutPrivate::UserHelpList) {
                    continue;
                }
                for (const auto &item : helpItem.list.firstColumn) {
                    maxWidth = std::max(int(item.size()), maxWidth);
                }
            }
        } else {
            maxWidth = 0;
        }

        const auto &cmdDesc = d->detailedDescription.empty() ? d->desc : d->detailedDescription;

        // Get last
        int last = int(helpLayoutData->itemDataList.size()) - 1;
        for (int i = last; i >= 0; --i) {
            const auto &item = helpLayoutData->itemDataList[i];

            bool empty = true;
            switch (item.itemType) {
                case HelpLayoutPrivate::HelpText: {
                    switch (static_cast<HelpLayout::HelpTextItem>(item.index)) {
                        case HelpLayout::HT_Prologue: {
                            if (noIntro)
                                break;
                            empty = parserData->prologue.empty();
                            break;
                        }
                        case HelpLayout::HT_Epilogue: {
                            if (noIntro)
                                break;
                            empty = parserData->epilogue.empty();
                            break;
                        }
                        case HelpLayout::HT_Description: {
                            if (noHelp)
                                break;
                            empty = cmdDesc.empty();
                            break;
                        }
                        case HelpLayout::HT_Usage: {
                            if (noHelp)
                                break;
                            empty = false;
                            break;
                        }
                    }
                    break;
                }
                case HelpLayoutPrivate::HelpList: {
                    if (noHelp)
                        break;
                    switch (static_cast<HelpLayout::HelpListItem>(item.index)) {
                        case HelpLayout::HL_Arguments: {
                            empty = argLists.size == 0;
                            break;
                        }
                        case HelpLayout::HL_Options: {
                            empty = optLists.size == 0;
                            break;
                        }
                        case HelpLayout::HL_Commands: {
                            empty = cmdLists.size == 0;
                            break;
                        }
                    }
                    break;
                }
                case HelpLayoutPrivate::Message: {
                    switch (static_cast<HelpLayout::MessageItem>(item.index)) {
                        case HelpLayout::MI_Information: {
                            empty = info.empty();
                            break;
                        }
                        case HelpLayout::MI_Warning: {
                            empty = warn.empty();
                            break;
                        }
                        case HelpLayout::MI_Critical: {
                            empty = err.empty();
                            break;
                        }
                    }
                    break;
                }
                case HelpLayoutPrivate::UserHelpText: {
                    if (noHelp)
                        break;
                    empty = item.text.lines.empty();
                    break;
                }
                case HelpLayoutPrivate::UserHelpList: {
                    if (noHelp)
                        break;
                    empty = item.list.firstColumn.empty();
                    break;
                }
                case HelpLayoutPrivate::UserIntro: {
                    if (noIntro)
                        break;
                    empty = false;
                    break;
                }
            }

            if (!empty) {
                last = i;
                break;
            }
        }

        // Output
        for (int i = 0; i <= last; ++i) {
            const auto &item = helpLayoutData->itemDataList[i];
            HelpLayout::Context ctx;
            ctx.parser = &parser;
            bool hasNext = i < last;
            ctx.hasNext = hasNext;
            switch (item.itemType) {
                case HelpLayoutPrivate::HelpText: {
                    HelpLayout::Text text;
                    ctx.text = &text;
                    switch (static_cast<HelpLayout::HelpTextItem>(item.index)) {
                        case HelpLayout::HT_Prologue: {
                            if (noIntro)
                                break;
                            text.lines = parserData->prologue;
                            break;
                        }
                        case HelpLayout::HT_Epilogue: {
                            if (noIntro)
                                break;
                            text.lines = parserData->epilogue;
                            break;
                        }
                        case HelpLayout::HT_Description: {
                            if (noHelp)
                                break;
                            text.title =
                                parserData->textProvider(Strings::Title, Strings::Description);
                            text.lines = cmdDesc;
                            break;
                        }
                        case HelpLayout::HT_Usage: {
                            if (noHelp)
                                break;
                            std::vector<Option> allOptions;
                            allOptions.reserve(core.globalOptionsSize);
                            for (int j = 0; j < core.globalOptionsSize; ++j) {
                                allOptions.emplace_back(*core.allOptionsResult[j].option);
                            }

                            {
                                // get parent names
                                auto p = &parserData->rootCommand;
                                for (int index : stack) {
                                    text.lines = p->name() + " ";
                                    p = &p->d_func()->commands[index];
                                }
                            }

                            void *a[2] = {
                                &allOptions,
                                reinterpret_cast<void *>(parserData->textProvider),
                            };
                            text.title = parserData->textProvider(Strings::Title, Strings::Usage);
                            text.lines += command->helpText(Symbol::HP_Usage, displayOptions, a);
                            break;
                        }
                    }
                    item.out(ctx);
                    break;
                }
                case HelpLayoutPrivate::HelpList: {
                    if (noHelp)
                        break;

                    const auto &listHasNext = [](int j, const Lists &lists) {
                        return j < lists.size - 1;
                    };

                    ctx.firstColumnLength = maxWidth;
                    switch (static_cast<HelpLayout::HelpListItem>(item.index)) {
                        case HelpLayout::HL_Arguments: {
                            for (int j = 0; j < argLists.size; ++j) {
                                ctx.hasNext = hasNext || listHasNext(j, argLists);
                                ctx.list = &argLists.data[j];
                                item.out(ctx);
                            }
                            break;
                        }
                        case HelpLayout::HL_Options: {
                            for (int j = 0; j < optLists.size; ++j) {
                                ctx.hasNext = hasNext || listHasNext(j, optLists);
                                ctx.list = &optLists.data[j];
                                item.out(ctx);
                            }
                            break;
                        }
                        case HelpLayout::HL_Commands: {
                            for (int j = 0; j < cmdLists.size; ++j) {
                                ctx.hasNext = hasNext || listHasNext(j, cmdLists);
                                ctx.list = &cmdLists.data[j];
                                item.out(ctx);
                            }
                            break;
                        }
                    }
                    break;
                }
                case HelpLayoutPrivate::Message: {
                    HelpLayout::Text text;
                    ctx.text = &text;
                    switch (static_cast<HelpLayout::MessageItem>(item.index)) {
                        case HelpLayout::MI_Information: {
                            text.lines = info;
                            break;
                        }
                        case HelpLayout::MI_Warning: {
                            text.lines = warn;
                            break;
                        }
                        case HelpLayout::MI_Critical: {
                            text.lines = err;
                            break;
                        }
                    }
                    item.out(ctx);
                    break;
                }
                case HelpLayoutPrivate::UserHelpText: {
                    if (noHelp)
                        break;
                    ctx.text = &item.text;
                    item.out(ctx);
                    break;
                }
                case HelpLayoutPrivate::UserHelpList: {
                    if (noHelp)
                        break;
                    ctx.list = &item.list;
                    ctx.firstColumnLength = maxWidth;
                    item.out(ctx);
                    break;
                }
                case HelpLayoutPrivate::UserIntro: {
                    if (noHelp)
                        break;
                    item.out(ctx);
                    break;
                }
            }
        }

        // Free
        delete[] argLists.data;
        delete[] optLists.data;
        delete[] cmdLists.data;
    }

    ParseResult::ParseResult() : SharedBase(nullptr) {
    }

    Command ParseResult::rootCommand() const {
        Q_D2(ParseResult);
        return d->parser.rootCommand();
    }

    const std::vector<std::string> &ParseResult::arguments() const {
        Q_D2(ParseResult);
        return d->arguments;
    }

    int ParseResult::invoke(int errCode) const {
        Q_D2(ParseResult);
        if (d->error != NoError) {
            showError();
            return errCode;
        }
        return dispatch();
    }

    int ParseResult::dispatch() const {
        Q_D2(ParseResult);
        if (d->error != NoError) {
            throw std::runtime_error("don't call dispatch when parsing fails");
        }

        const auto &cmdData = d->command->d_func();
        const auto &handler = cmdData->handler;

        // If version is empty, you should do something in the handler
        if (d->roleSet[Option::Version] && !cmdData->version.empty()) {
            u8info("%s\n", cmdData->version.data());
            return 0;
        }

        if (d->roleSet[Option::Help]) {
            showHelpText();
            return 0;
        }

        if (!handler) {
            throw std::runtime_error(
                Utils::formatText(R"(command "%1" doesn't have a valid handler)", {
                                                                                      cmdData->name,
                                                                                  }));
        }

        return handler(*this);
    }

    ParseResult::Error ParseResult::error() const {
        Q_D2(ParseResult);
        return d->error;
    }

    std::string ParseResult::errorText() const {
        Q_D2(ParseResult);
        if (d->error == NoError)
            return {};
        return Utils::formatText(d->parser.d_func()->textProvider(Strings::ParseError, d->error),
                                 d->errorPlaceholders);
    }

    std::string ParseResult::correctionText() const {
        Q_D2(ParseResult);
        return d->correctionText();
    }

    std::string ParseResult::cancellationToken() const {
        Q_D2(ParseResult);
        return d->cancellationToken;
    }

    Command ParseResult::command() const {
        Q_D2(ParseResult);
        return *d->command;
    }

    std::vector<Option> ParseResult::globalOptions() const {
        Q_D2(ParseResult);
        return d->globalOptions();
    }

    std::vector<int> ParseResult::commandIndexStack() const {
        Q_D2(ParseResult);
        return d->stack;
    }

    int ParseResult::indexOfArgument(const std::string &name) const {
        Q_D2(ParseResult);
        auto it = d->core.argNameIndexes.find(name);
        if (it == d->core.argNameIndexes.end())
            return -1;
        return it->second.i;
    }

    int ParseResult::indexOfOption(const std::string &token) const {
        Q_D2(ParseResult);
        auto it = d->core.allOptionTokenIndexes.find(token);
        if (it == d->core.allOptionTokenIndexes.end())
            return -1;
        return it->second.i;
    }

    void ParseResult::showError() const {
        Q_D2(ParseResult);
        if (d->error == NoError)
            return;

        const auto &parserData = d->parser.d_func();
        const auto &displayOptions = parserData->displayOptions;
        d->showMessage(
            (displayOptions & Parser::SkipCorrection) ? std::string() : d->correctionText(), {},
            parserData->textProvider(Strings::Title, Strings::Error) + ": " + errorText(), true);
    }

    void ParseResult::showHelpText() const {
        Q_D2(ParseResult);
        d->showMessage({}, {}, {});
    }

    void ParseResult::showMessage(const std::string &info, const std::string &warn,
                                  const std::string &err) const {
        Q_D2(ParseResult);
        const auto &displayOptions = d->parser.d_func()->displayOptions;
        d->showMessage(info, warn, err, true);
    }

    bool ParseResult::isRoleSet(Option::Role role) const {
        Q_D2(ParseResult);
        return d->roleSet[role];
    }

    const std::vector<Value> &ParseResult::values(int index) const {
        Q_D2(ParseResult);
        if (index < 0 || index >= d->core.argSize)
            return sharedEmptyValues();
        return d->core.argResult[index];
    }

    Value ParseResult::value(int index) const {
        Q_D2(ParseResult);
        if (index < 0 || index >= d->core.argSize)
            return {};
        const auto &args = d->core.argResult[index];
        return args.empty() ? d->command->d_func()->arguments[index].defaultValue() : args.front();
    }

    OptionResult ParseResult::option(int index) const {
        Q_D2(ParseResult);
        if (index < 0 || index >= d->core.allOptionsSize)
            return {};
        return {&d->core.allOptionsResult[index]};
    }

    ParseResult::ParseResult(ParseResultPrivate *d) : SharedBase(d) {
    }

}