#ifndef OPTION_P_H
#define OPTION_P_H

#include "argument_p.h"
#include "option.h"

namespace SysCmdLine {

    class OptionPrivate : public ArgumentHolderPrivate {
    public:
        OptionPrivate(Option::Role role, const std::vector<std::string> &tokens,
                      const std::string &desc, bool required);

        SymbolPrivate *clone() const override;

    public:
        Option::Role role;
        std::vector<std::string> tokens;
        bool required;
        Option::ShortMatchRule shortMatchRule;
        Option::PriorLevel priorLevel;
        bool global;
        int maxOccurrence;

        static std::vector<Option> reorderOptions(const std::vector<Option> &options,
                                                  const std::vector<Option> &globalOptions);
    };

}

#endif // OPTION_P_H
