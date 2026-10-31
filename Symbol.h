//
// Created by aven on 30/10/2026.
//

#ifndef WEIRD_REPL_SYMBOL_H
#define WEIRD_REPL_SYMBOL_H
#include <string>

namespace Runtime {
    struct Symbol {
        virtual ~Symbol() = default;
    };

    struct Str : Symbol { std::string value; };
    struct Bool : Symbol { bool value; };
    struct Num : Symbol { double value; };
}

#endif //WEIRD_REPL_SYMBOL_H
