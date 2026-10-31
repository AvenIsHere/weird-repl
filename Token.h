//
// Created by aven on 30/10/2026.
//

#ifndef WEIRD_REPL_TOKEN_H
#define WEIRD_REPL_TOKEN_H
#include <string>
#include <utility>

namespace Lexer {

    enum class TokenType {
        Add,
        Sub,
        Mult,
        Divide,
        Exponent,
        EqualityOp,
        NotOp,
        GreaterOp,
        LessOp,
        LeftParen,
        RightParen,
        Num,
        Str,
        Bool
    };

    struct Token {
        TokenType type;
        Token(const TokenType type) : type(type) {}
        virtual ~Token() = default;
    };

    struct LiteralToken : Token {
        std::string value;
        LiteralToken(const TokenType type, std::string value) : Token(type), value(std::move(value)) {}
    };
}

#endif //WEIRD_REPL_TOKEN_H
