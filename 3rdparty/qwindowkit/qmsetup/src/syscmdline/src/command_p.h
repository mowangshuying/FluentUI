#ifndef COMMAND_P_H
#define COMMAND_P_H

#include "argument_p.h"
#include "command.h"

#include "map_p.h"

namespace SysCmdLine {

    class CommandCataloguePrivate : public SharedBasePrivate {
    public:
        SharedBasePrivate *clone() const;

        StringListMapWrapper arg;
        StringListMapWrapper opt;
        StringListMapWrapper cmd;

        StringList arguments;
        StringList options;
        StringList commands;
    };

    class CommandPrivate : public ArgumentHolderPrivate {
    public:
        CommandPrivate(std::string name, const std::string &desc);

        SharedBasePrivate *clone() const override;

    public:
        std::string name;

        std::vector<Option> options;
        std::vector<std::string> optionGroupNames;
        std::vector<Command> commands;

        std::string version;
        std::string detailedDescription;
        CommandCatalogue catalogue;

        Command::Handler handler;
        
        HelpLayout helpLayout;

#ifdef SYSCMDLINE_ENABLE_VALIDITY_CHECK
        void checkAddedCommand(const Command &cmd) const;
        void checkAddedOption(const Option &opt, const std::string &exclusiveGroup) const;
#endif
    };

}

#endif // COMMAND_P_H
