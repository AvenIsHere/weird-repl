//
// Created by aven on 30/10/2026.
//

#ifndef WEIRD_REPL_ASTNODE_H
#define WEIRD_REPL_ASTNODE_H
#include <memory>

namespace AST {

    enum class NodeType {
        Add,
        Mult,
        Exponent,
        Equality,
        Not,
        Num,
        Bool,
        Str
    };

    struct Node {
    private:
        NodeType type;
    public:
        Node(NodeType type) : type(type) {}
        [[nodiscard]] NodeType get_type() const {return type;}
        virtual ~Node() = default;
    };

    struct BinaryNode : Node {
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        BinaryNode(const NodeType type, std::unique_ptr<Node> left, std::unique_ptr<Node> right) : Node(type), left(std::move(left)), right(std::move(right)) {}
    };

    struct UnaryNode : Node {
        std::unique_ptr<Node> operand;
        UnaryNode(const NodeType type, std::unique_ptr<Node> operand) : Node(type), operand(std::move(operand)) {}
    };

    struct NumNode : Node {
        double value;
        NumNode(const double val) : Node(NodeType::Num), value(val) {}
    };

    struct BoolNode : Node {
        bool value;
        BoolNode(const bool val) : Node(NodeType::Bool), value(val) {}
    };

    struct StrNode : Node {
        std::string value;
        StrNode(std::string val) : Node(NodeType::Str), value(std::move(val)) {}
    };

    inline std::unique_ptr<Node> Add(std::unique_ptr<Node> left, std::unique_ptr<Node> right) {
        return std::make_unique<BinaryNode>(NodeType::Add, std::move(left), std::move(right));
    }
    inline std::unique_ptr<Node> Mult(std::unique_ptr<Node> left, std::unique_ptr<Node> right) {
        return std::make_unique<BinaryNode>(NodeType::Mult, std::move(left), std::move(right));
    }
    inline std::unique_ptr<Node> Exponent(std::unique_ptr<Node> left, std::unique_ptr<Node> right) {
        return std::make_unique<BinaryNode>(NodeType::Exponent, std::move(left), std::move(right));
    }
    inline std::unique_ptr<Node> Equality(std::unique_ptr<Node> left, std::unique_ptr<Node> right) {
        return std::make_unique<BinaryNode>(NodeType::Equality, std::move(left), std::move(right));
    }
    inline std::unique_ptr<Node> Not(std::unique_ptr<Node> operand) {
        return std::make_unique<UnaryNode>(NodeType::Not, std::move(operand));
    }
    inline std::unique_ptr<Node> Num(const double val) {
        return std::make_unique<NumNode>(val);
    }
    inline std::unique_ptr<Node> Bool(const bool val) {
        return std::make_unique<BoolNode>(val);
    }
    inline std::unique_ptr<Node> Str(std::string val) {
        return std::make_unique<StrNode>(std::move(val));
    }

}

#endif //WEIRD_REPL_ASTNODE_H
