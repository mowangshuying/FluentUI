#ifndef ARGUMENT_P_H
#define ARGUMENT_P_H

#include "argument.h"
#include "symbol_p.h"

namespace SysCmdLine {

    class ArgumentPrivate : public SymbolPrivate {
    public:
        ArgumentPrivate(std::string name, const std::string &desc, bool required,
                        Value defaultValue);

        SymbolPrivate *clone() const override;

    public:
        std::string name;
        bool required;
        Value defaultValue;
        std::vector<Value> expectedValues;
        std::string displayName;
        Argument::Number number;
        Argument::Validator validator;
    };

    class ArgumentHolderPrivate : public SymbolPrivate {
    public:
        ArgumentHolderPrivate(Symbol::SymbolType type, const std::string &desc);

    public:
        std::vector<Argument> arguments;

#ifdef SYSCMDLINE_ENABLE_VALIDITY_CHECK
        void checkAddedArgument(const Argument &arg) const;
#endif
    };

}

#endif // ARGUMENT_P_H
