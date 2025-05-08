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

#ifndef COMMAND_H
#define COMMAND_H

#include <syscmdline/option.h>
#include <syscmdline/helplayout.h>

namespace SysCmdLine {

    class ParseResult;

    class CommandCataloguePrivate;

    class SYSCMDLINE_EXPORT CommandCatalogue : public SharedBase {
        SYSCMDLINE_DECL_PRIVATE(CommandCatalogue)
    public:
        CommandCatalogue();

    public:
        void addArguments(const std::string &name, const std::vector<std::string> &args);
        void addOptions(const std::string &name, const std::vector<std::string> &options);
        void addCommands(const std::string &name, const std::vector<std::string> &commands);
    };

    class CommandPrivate;

    class SYSCMDLINE_EXPORT Command : public ArgumentHolder {
        SYSCMDLINE_DECL_PRIVATE(Command)
    public:
        using Handler = std::function<int /* code */ (const ParseResult & /* result */)>;

        Command();
        Command(const std::string &name, const std::string &desc = {},
                const std::vector<Argument> &args = {});

        using Symbol::helpText;
        std::string helpText(HelpPosition pos, int displayOptions, void *extra) const override;

    public:
        std::string name() const;
        void setName(const std::string &name);

        inline void addOption(const Option &option, const std::string &group = {});
        void addOptions(const std::vector<Option> &options, const std::string &group = {});

        int commandCount() const;
        Command command(int index) const;
        inline void addCommand(const Command &command);
        void addCommands(const std::vector<Command> &commands);

        std::string detailedDescription() const;
        void setDetailedDescription(const std::string &detailedDescription);

        Handler handler() const;
        void setHandler(const Handler &handler);

        CommandCatalogue catalogue() const;
        void setCatalogue(const CommandCatalogue &catalogue);

        std::string versionString() const;

        void addVersionOption(const std::string &version,
                              const std::vector<std::string> &tokens = {},
                              const std::string &desc = {});
        void addHelpOption(bool showHelpIfNoArg = false, bool global = false,
                           const std::vector<std::string> &tokens = {},
                           const std::string &desc = {});

        HelpLayout helpLayout() const;
        void setHelpLayout(const HelpLayout &helpLayout);

    public:
        inline Command &detailed(const std::string &detailedDescription);
        inline Command &action(const Handler &handler);
        inline Command &catalog(const CommandCatalogue &catalogue);
        inline Command &version(const std::string &version,
                                const std::vector<std::string> &tokens = {},
                                const std::string &desc = {});
        inline Command &help(bool showHelpIfNoArg = false, bool global = false,
                             const std::vector<std::string> &tokens = {},
                             const std::string &desc = {});
    };

    inline void Command::addCommand(const Command &command) {
        addCommands({command});
    }

    inline void Command::addOption(const Option &option, const std::string &group) {
        addOptions({option}, group);
    }

    inline Command &Command::detailed(const std::string &detailedDescription) {
        setDetailedDescription(detailedDescription);
        return *this;
    }

    inline Command &Command::action(const Command::Handler &handler) {
        setHandler(handler);
        return *this;
    }

    inline Command &Command::catalog(const CommandCatalogue &catalogue) {
        setCatalogue(catalogue);
        return *this;
    }

    inline Command &Command::version(const std::string &version,
                                     const std::vector<std::string> &tokens,
                                     const std::string &desc) {
        addVersionOption(version, tokens, desc);
        return *this;
    }

    inline Command &Command::help(bool showHelpIfNoArg, bool global,
                                  const std::vector<std::string> &tokens, const std::string &desc) {
        addHelpOption(showHelpIfNoArg, global, tokens, desc);
        return *this;
    }

}

#endif // COMMAND_H
