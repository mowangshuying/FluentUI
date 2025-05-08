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

#ifndef PARSER_H
#define PARSER_H

#include <syscmdline/parseresult.h>

namespace SysCmdLine {

    class ParserPrivate;

    class SYSCMDLINE_EXPORT Parser : public SharedBase {
        SYSCMDLINE_DECL_PRIVATE(Parser)
    public:
        Parser();
        Parser(const Command &rootCommand);

    public:
        enum ParseOption {
            Standard = 0,
            IgnoreCommandCase = 0x1,
            IgnoreOptionCase = 0x2,
            AllowUnixGroupFlags = 0x4,
            AllowDosShortOptions = 0x8,
            DontAllowUnixShortOptions = 0x10,
        };

        enum DisplayOption {
            Normal = 0,
            DontShowHelpOnError = 0x1,
            DontShowIntroOnError = 0x2,
            SkipCorrection = 0x4,
            ShowArgumentDefaultValue = 0x8,
            ShowArgumentExpectedValues = 0x10,
            ShowArgumentIsRequired = 0x20,
            ShowOptionIsRequired = 0x40,
            AlignAllCatalogues = 0x80,
            DontShowRequiredOptionsOnUsage = 0x100,
            ShowOptionalOptionsOnUsage = 0x200,
            ShowOptionsBehindArguments = 0x400,
            ShowOptionsHintFront = 0x800,
        };

        std::string prologue() const;
        void setPrologue(const std::string &prologue);

        std::string epilogue() const;
        void setEpilogue(const std::string &epilogue);

        int displayOptions() const;
        void setDisplayOptions(int displayOptions);

        Command rootCommand() const;
        void setRootCommand(const Command &rootCommand);

        ParseResult parse(const std::vector<std::string> &args, int parseOptions = Standard);
        inline int invoke(const std::vector<std::string> &args, int errCode = -1,
                          int parseOptions = Standard);

        // Don't use this pair of API on Windows because the arguemnts passed by `main`
        // entry is in ANSI encoding, but the library uses UTF-8.
        inline ParseResult parse(int argc, char **argv, int parseOptions = Standard);
        inline int invoke(int argc, char **argv, int errCode = -1, int parseOptions = Standard);

    public:
        using TextProvider = std::string (*)(int /* category */, int /* index */);

        enum SizeType {
            ST_Indent,
            ST_Spacing,
            ST_ConsoleWidth,
        };
        int size(SizeType sizeType) const;
        void setSize(SizeType sizeType, int value);

        TextProvider textProvider();
        void setTextProvider(TextProvider textProvider);

        static TextProvider defaultTextProvider();
    };

    inline int Parser::invoke(const std::vector<std::string> &args, int errCode, int parseOptions) {
        return parse(args, parseOptions).invoke(errCode);
    }

    inline ParseResult Parser::parse(int argc, char **argv, int parseOptions) {
        return parse({argv, argv + argc}, parseOptions);
    }

    inline int Parser::invoke(int argc, char **argv, int errCode, int parseOptions) {
        return parse({argv, argv + argc}, parseOptions).invoke(errCode);
    }

}

#endif // PARSER_H
