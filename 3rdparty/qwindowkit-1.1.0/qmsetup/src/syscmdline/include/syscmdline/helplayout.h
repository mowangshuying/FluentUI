/****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2023 SineStriker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ****************************************************************************/

#ifndef HELPLAYOUT_H
#define HELPLAYOUT_H

#include <string>
#include <vector>
#include <functional>

#include <syscmdline/sharedbase.h>

namespace SysCmdLine {

    class Parser;

    class HelpLayoutPrivate;

    class SYSCMDLINE_EXPORT HelpLayout : public SharedBase {
        SYSCMDLINE_DECL_PRIVATE(HelpLayout)
    public:
        HelpLayout();

        enum HelpTextItem {
            HT_Prologue,
            HT_Epilogue,
            HT_Description,
            HT_Usage,
        };

        enum HelpListItem {
            HL_Arguments,
            HL_Options,
            HL_Commands,
        };

        enum MessageItem {
            MI_Information,
            MI_Warning,
            MI_Critical,
        };

        struct Text {
            std::string title;
            std::string lines;
        };

        struct List {
            std::string title;
            std::vector<std::string> firstColumn;
            std::vector<std::string> secondColumn;
        };

        struct Context {
            const Parser *parser;
            union {
                // Available on `HelpTextItem`, `UserHelpTextItem`
                const Text *text;

                // Available on `HelpListItem`, `UserHelpListItem`
                struct {
                    const List *list;
                    int firstColumnLength;
                };
            };
            bool hasNext;
        };

        using Output = std::function<void(const Context & /* context */)>;

    public:
        void addHelpTextItem(HelpTextItem type, const Output &out = {});
        void addHelpListItem(HelpListItem type, const Output &out = {});
        void addMessageItem(MessageItem type, const Output &out = {});

        void addUserHelpTextItem(const Text &text, const Output &out = {});
        void addUserHelpListItem(const List &list, const Output &out = {});
        void addUserIntroItem(const Output &out);

    public:
        static HelpLayout defaultHelpLayout();
    };

}

#endif // HELPLAYOUT_H
