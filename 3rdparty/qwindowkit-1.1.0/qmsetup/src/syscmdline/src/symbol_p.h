#ifndef SYMBOL_P_H
#define SYMBOL_P_H

#include <atomic>

#include "symbol.h"
#include "sharedbase_p.h"

namespace SysCmdLine {

    class SymbolPrivate : public SharedBasePrivate {
    public:
        SymbolPrivate(Symbol::SymbolType type, std::string desc);

    public:
        Symbol::SymbolType type;
        std::string desc;
        Symbol::HelpProvider helpProvider;
    };

}

#endif // SYMBOL_P_H
