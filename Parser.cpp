//
// Created by aven on 01/11/2026.
//

#include "Parser.h"

#include <format>

size_t Parser::find_matching_bracket(size_t search_pos) const {
    search_pos++;
    unsigned int paren_stack = 0;
    while (search_pos < tokens.size()) {
        if (tokens[search_pos]->type == Lexer::TokenType::LeftParen) {
            paren_stack++;
        }
        else if (tokens[search_pos]->type == Lexer::TokenType::RightParen) {
            if (paren_stack == 0) return search_pos;
            paren_stack--;
        }
        search_pos++;
    }
    throw std::runtime_error(std::format("Unclosed parenthesis"));
}

std::unique_ptr<AST::Node> Parser::get_node() {
    if (tokens[pos]->type == Lexer::TokenType::LeftParen) {
        const auto bracket_end = find_matching_bracket(pos);
        pos++;
        auto inner = parse(bracket_end - 1);
        pos = bracket_end + 1;
        return inner;
    }
    if (tokens[pos]->type == Lexer::TokenType::Str) {
        const auto literal = dynamic_cast<Lexer::LiteralToken*>(tokens[pos].get());
        return AST::Str(literal->value);
    }
    if (tokens[pos]->type == Lexer::TokenType::Num) {
        const auto literal = dynamic_cast<Lexer::LiteralToken*>(tokens[pos].get());
        const double val = stod(literal->value);
        return AST::Num(val);
    }
    if (tokens[pos]->type == Lexer::TokenType::Bool) {
        const auto literal = dynamic_cast<Lexer::LiteralToken*>(tokens[pos].get());
        const bool val = literal->value == "true";
        return AST::Bool(val);
    }
    if (tokens[pos]->type == Lexer::TokenType::NotOp) {
        pos++;
        auto operand = get_node();
        return AST::Not(std::move(operand));
    }
    throw std::runtime_error("Unexpected token");
}

std::unique_ptr<AST::Node> Parser::parse(size_t end) {
    auto node = get_node();

    while (pos < end && pos < tokens.size()) {
        const auto op_type = tokens[pos]-> type;

        if (op_type == Lexer::TokenType::Add) {
            pos++;
            auto right = get_node();
            node = AST::Add(std::move(node), std::move(right));
        }
    }
}