//
// Created by aven on 01/11/2026.
//

#ifndef WEIRD_REPL_PARSER_H
#define WEIRD_REPL_PARSER_H
#include <memory>
#include <utility>
#include <vector>

#include "ASTNode.h"
#include "Token.h"


class Parser {

    std::vector<std::unique_ptr<Lexer::Token>> tokens;
    size_t pos;

    [[nodiscard]] size_t find_matching_bracket(size_t search_pos) const;

    std::unique_ptr<AST::Node> get_node();
    std::unique_ptr<AST::Node> parse(size_t end);

public:

    explicit Parser(std::vector<std::unique_ptr<Lexer::Token>> tokens) : tokens(std::move(tokens)), pos(0) {}
    std::unique_ptr<AST::Node> get_ast();

};


#endif //WEIRD_REPL_PARSER_H
