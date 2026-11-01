//
// Created by aven on 30/10/2026.
//

#include "Repl.h"

#include <iostream>
#include <unordered_map>

static std::unordered_map<Lexer::TokenType, std::string> token_str = {
    {Lexer::TokenType::Add, "TokenType::Add"},
    {Lexer::TokenType::Sub, "TokenType::Sub"},
    {Lexer::TokenType::Mult, "TokenType::Mult"},
    {Lexer::TokenType::Divide, "TokenType::Divide"},
    {Lexer::TokenType::Exponent, "TokenType::Exponent"},
    {Lexer::TokenType::EqualityOp, "TokenType::EqualityOp"},
    {Lexer::TokenType::NotOp, "TokenType::NotOp"},
    {Lexer::TokenType::GreaterOp, "TokenType::GreaterOp"},
    {Lexer::TokenType::LessOp, "TokenType::LessOp"},
    {Lexer::TokenType::LeftParen, "TokenType::LeftParen"},
    {Lexer::TokenType::RightParen, "TokenType::RightParen"},
    {Lexer::TokenType::Num, "TokenType::Num"},
    {Lexer::TokenType::Str, "TokenType::Str"},
    {Lexer::TokenType::Bool, "TokenType::Bool"}
};

void output_tokens(const std::vector<std::unique_ptr<Lexer::Token>>& tokens) {
    for (const auto& token : tokens) {
        if (token->type == Lexer::TokenType::Num || token->type == Lexer::TokenType::Bool || token->type == Lexer::TokenType::Str) {
            const auto token_num = dynamic_cast<Lexer::LiteralToken*>(token.get());
            std::cout << "<" << token_str[token->type] << ", \"" << token_num->value << "\"> ";
        }
        else {
            std::cout << "<" << token_str[token->type] << "> ";
        }
    }
    std::cout << std::endl;
}

Repl::Repl() {
    lexer = Lexer::Lexer();
}

void Repl::loop() {
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        output_tokens(lexer.tokenise(input));
    }
}
