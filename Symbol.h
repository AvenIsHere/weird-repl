//
// Created by aven on 30/10/2026.
//

#ifndef WEIRD_REPL_SYMBOL_H
#define WEIRD_REPL_SYMBOL_H
#include <string>

namespace Runtime {

    enum class SymbolType {
        Str,
        Bool,
        Num
    };

    struct Symbol {
        SymbolType type;
        Symbol(const SymbolType type) : type(type) {}
        virtual ~Symbol() = default;
    };

    struct Str : Symbol {
        std::string value;
        Str(std::string val) : Symbol(SymbolType::Str), value(std::move(val)) {}
    };
    struct Bool : Symbol {
        bool value;
        Bool(const bool val) : Symbol(SymbolType::Bool), value(val) {}
    };
    struct Num : Symbol {
        double value;
        Num(const double val) : Symbol(SymbolType::Num), value(val) {}
    };
}

#endif //WEIRD_REPL_SYMBOL_H
