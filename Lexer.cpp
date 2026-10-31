//
// Created by aven on 30/10/2026.
//

#include "Lexer.h"

#include <format>
#include <memory>

Lexer::Lexer::Lexer() {
    char_index = 0;
}

std::string Lexer::Lexer::get_num(const std::string& input) {
    std::string return_str{};
    bool seen_period = false;
    while (true) {
        if (!isdigit(input[char_index]) && input[char_index] != '.') {
            char_index--;
            break;
        }
        if (input[char_index] == '.') {
            if (seen_period) throw std::runtime_error("Malformed number literal");
            seen_period = true;
        }
        return_str.push_back(input[char_index]);
        if (char_index + 1 >= input.size()) break;
        char_index++;
    }
    return return_str;
}

std::string Lexer::Lexer::get_ident(const std::string &input) {
    std::string return_str{};
    while (true) {
        if (!isalnum(input[char_index]) && input[char_index] != '_') {
            char_index--;
            break;
        }
        return_str.push_back(input[char_index]);
        if (char_index + 1 >= input.size()) break;
        char_index++;
    }
    return return_str;
}

std::string Lexer::Lexer::get_str(const std::string &input, const char quote_char) {
    std::string return_str{};
    while (true) {
        if (char_index + 1 >= input.size()) throw std::runtime_error("Unterminated string");
        char_index++;
        if (input[char_index] == quote_char) break;
        return_str.push_back(input[char_index]);
    }
    return return_str;
}

std::optional<char> Lexer::Lexer::get_next_token(std::string input) const {
    if (char_index + 1 >= input.size()) return std::nullopt;
    return input[char_index + 1];
}

std::unique_ptr<Lexer::Token> Lexer::Lexer::parse_token(const std::string &input) {
    switch (input[char_index]) {
        case '+': {
            return std::make_unique<Token>(TokenType::Add);
        }
        case '-': {
            return std::make_unique<Token>(TokenType::Sub);
        }
        case '*': {
            return std::make_unique<Token>(TokenType::Mult);
        }
        case '/': {
            return std::make_unique<Token>(TokenType::Divide);
        }
        case '^': {
            return std::make_unique<Token>(TokenType::Exponent);
        }
        case '=': {
            const auto next_token = get_next_token(input);
            if (!next_token || next_token.value() != '=') throw std::runtime_error("Unexpected token '='");
            char_index++;
            return std::make_unique<Token>(TokenType::EqualityOp);
        }
        case '!': {
            return std::make_unique<Token>(TokenType::NotOp);
        }
        case '>': {
            return std::make_unique<Token>(TokenType::GreaterOp);
        }
        case '<': {
            return std::make_unique<Token>(TokenType::LessOp);
        }
        case '(': {
            return std::make_unique<Token>(TokenType::LeftParen);
        }
        case ')': {
            return std::make_unique<Token>(TokenType::RightParen);
        }
        case '\'':
        case '"': {
            return std::make_unique<LiteralToken>(TokenType::Str, get_str(input, input[char_index]));
        }
        default: {
            if (input[char_index] == '_' || isalpha(input[char_index])) {
                const auto ident = get_ident(input);
                if (ident == "true" || ident == "false") return std::make_unique<LiteralToken>(TokenType::Bool, ident);
                throw std::runtime_error(std::format("Unknown keyword \"{}\"", ident));
            }
            if (isdigit(input[char_index]) || input[char_index] == '.') {
                return std::make_unique<LiteralToken>(TokenType::Num, get_num(input));
            }
        }
    }
    throw std::runtime_error("Unknown token");
}

std::vector<std::unique_ptr<Lexer::Token>> Lexer::Lexer::tokenise(const std::string& input) {

    std::vector<std::unique_ptr<Token>> tokens;
    for (char_index = 0; char_index < input.size(); char_index++) {
        if (input[char_index] == ' ') continue;
        tokens.emplace_back(parse_token(input));
    }
    return tokens;
}
