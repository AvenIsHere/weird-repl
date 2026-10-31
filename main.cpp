#include <iostream>
#include <unordered_map>

#include "Lexer.h"

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

int main() {

    std::string input;
    std::getline(std::cin, input);
    Lexer::Lexer lexer{};
    for (const auto output = lexer.tokenise(input); const auto& token : output) {
        if (token->type == Lexer::TokenType::Num || token->type == Lexer::TokenType::Bool || token->type == Lexer::TokenType::Str) {
            const auto token_num = dynamic_cast<Lexer::LiteralToken*>(token.get());
            std::cout << "<" << token_str[token->type] << ", \"" << token_num->value << "\">" << std::endl;
        }
        else {
            std::cout << "<" << token_str[token->type] << ">" << std::endl;
        }
    }

}