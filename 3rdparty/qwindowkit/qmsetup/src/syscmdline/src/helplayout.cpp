#include "helplayout.h"
#include "helplayout_p.h"

#include <algorithm>

#include "system.h"
#include "parser_p.h"
#include "utils_p.h"

namespace SysCmdLine {

    static inline void printLast(bool hasNext) {
        if (hasNext)
            u8info("\n");
    }

    static void defaultTextsPrinter(MessageType messageType, bool highlight,
                                    const HelpLayout::Context &ctx) {
        if (ctx.text->lines.empty())
            return;
        if (ctx.text->title.empty()) {
            // Content
            u8debug(messageType, highlight, "%s\n", ctx.text->lines.data());
        } else {
            // Title
            u8debug(messageType, highlight, "%s:\n", ctx.text->title.data());

            // Content
            auto lines = Utils::split(ctx.text->lines, "\n");
            for (const auto &line : std::as_const(lines))
                u8debug(messageType, highlight, "%s%s\n", ctx.parser->d_func()->indent().data(),
                        line.data());
        }
        printLast(ctx.hasNext);
    }

    static void defaultInfoPrinter(const HelpLayout::Context &ctx) {
        defaultTextsPrinter(MT_Debug, false, ctx);
    }

    static void defaultWarnPrinter(const HelpLayout::Context &ctx) {
        defaultTextsPrinter(MT_Warning, false, ctx);
    }

    static void defaultErrorPrinter(const HelpLayout::Context &ctx) {
        defaultTextsPrinter(MT_Critical, true, ctx);
    }

    static void defaultListPrinter(const HelpLayout::Context &ctx) {
        if (ctx.list->firstColumn.empty())
            return;

        // Title
        u8info("%s:\n", ctx.text->title.data());

        const auto &list = ctx.list;
        const auto &parserData = ctx.parser->d_func();

        int widest = ctx.firstColumnLength;
        if (widest == 0) {
            for (const auto &item : list->firstColumn)
                widest = std::max(widest, int(item.size()));
        }

        std::vector<std::string> res;
        for (size_t i = 0; i < list->firstColumn.size(); ++i) {
            const auto &first = list->firstColumn[i];
            const auto &second = list->secondColumn[i];

            auto lines = Utils::split(second, "\n");
            if (lines.empty())
                lines.emplace_back();

            {
                std::string ss;
                ss += parserData->indent();
                ss += first;
                ss += std::string(widest - first.size(), ' ');
                ss += parserData->spacing();
                ss += lines.front();
                res.push_back(ss);
            }

            for (size_t j = 1; j < lines.size(); ++j) {
                std::string ss;
                ss += parserData->indent();
                ss += std::string(widest, ' ');
                ss += parserData->spacing();
                ss += std::as_const(lines)[j];
                res.push_back(ss);
            }
        }

        for (const auto &line : std::as_const(res)) {
            u8info("%s\n", line.data());
        }

        printLast(ctx.hasNext);
    }

    HelpLayout::HelpLayout() : SharedBase(new HelpLayoutPrivate()) {
    }

    void HelpLayout::addHelpTextItem(HelpTextItem type, const Output &out) {
        Q_D(HelpLayout);
        d->itemDataList.push_back(
            {HelpLayoutPrivate::HelpText, type, out ? out : defaultInfoPrinter, {}, {}});
    }
    void HelpLayout::addHelpListItem(HelpListItem type, const Output &out) {
        Q_D(HelpLayout);
        d->itemDataList.push_back(
            {HelpLayoutPrivate::HelpList, type, out ? out : defaultListPrinter, {}, {}});
    }
    void HelpLayout::addMessageItem(MessageItem type, const Output &out) {
        Q_D(HelpLayout);
        d->itemDataList.push_back({HelpLayoutPrivate::Message, type, out ? out : [](MessageItem item) {
                                       switch (item) {
                                           case MI_Warning:
                                               return defaultWarnPrinter;
                                           case MI_Critical:
                                               return defaultErrorPrinter;
                                           default:
                                               break ;
                                       }
                                       return defaultInfoPrinter;
                                   }(type), {}, {}});
    }
    void HelpLayout::addUserHelpTextItem(const Text &text, const Output &out) {
        Q_D(HelpLayout);
        d->itemDataList.push_back(
            {HelpLayoutPrivate::UserHelpText, 0, out ? out : defaultInfoPrinter, text, {}});
    }
    void HelpLayout::addUserHelpListItem(const List &list, const Output &out) {
        Q_D(HelpLayout);
        d->itemDataList.push_back(
            {HelpLayoutPrivate::UserHelpList, 0, out ? out : defaultListPrinter, {}, list});
    }
    void HelpLayout::addUserIntroItem(const Output &out) {
        Q_D(HelpLayout);
        d->itemDataList.push_back({HelpLayoutPrivate::UserIntro, 0, out, {}, {}});
    }

    HelpLayout HelpLayout::defaultHelpLayout() {
        static HelpLayout instance = []() {
            HelpLayout res;
            res.addHelpTextItem(HT_Prologue);
            res.addMessageItem(MI_Information);
            res.addMessageItem(MI_Warning);
            res.addMessageItem(MI_Critical);
            res.addHelpTextItem(HT_Description);
            res.addHelpTextItem(HT_Usage);
            res.addHelpListItem(HL_Arguments);
            res.addHelpListItem(HL_Options);
            res.addHelpListItem(HL_Commands);
            res.addHelpTextItem(HT_Epilogue);
            return res;
        }();
        return instance;
    }

}