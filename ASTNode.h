//
// Created by aven on 30/10/2026.
//

#ifndef WEIRD_REPL_ASTNODE_H
#define WEIRD_REPL_ASTNODE_H
#include <memory>

namespace AST {
    struct Node {
        virtual ~Node() = default;
    };

    struct Add : Node {
        std::unique_ptr<Node> left_op;
        std::unique_ptr<Node> right_op;
    };

    struct Mult : Node {
        std::unique_ptr<Node> left_op;
        std::unique_ptr<Node> right_op;
    };

    struct Exponent : Node {
        std::unique_ptr<Node> base;
        std::unique_ptr<Node> exponent;
    };

    struct Equality : Node {
        std::unique_ptr<Node> left_op;
        std::unique_ptr<Node> right_op;
    };

    struct Not : Node {
        std::unique_ptr<Node> value;
    };

    struct Num : Node {
        double value;
    };

    struct Bool : Node {
        bool value;
    };

    struct Str : Node {
        std::string value;
    };
}

#endif //WEIRD_REPL_ASTNODE_H
