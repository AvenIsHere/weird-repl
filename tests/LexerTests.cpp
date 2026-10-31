//
// Created by aven on 31/10/2026.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "Lexer.h"

Lexer::Lexer test_lexer{};

bool check_token_equal(const std::unique_ptr<Lexer::Token> &token1, const std::unique_ptr<Lexer::Token> &token2) {

    if (token1->type != token2->type) return false;
    if (token1->type == Lexer::TokenType::Num ||
        token1->type == Lexer::TokenType::Str ||
        token1->type == Lexer::TokenType::Bool) {
        const auto token1_literal = dynamic_cast<Lexer::LiteralToken*>(token1.get());
        const auto token2_literal = dynamic_cast<Lexer::LiteralToken*>(token2.get());
        if (token1_literal->value != token2_literal->value) return false;
    }
    return true;
}

BOOST_AUTO_TEST_SUITE(lexer_test)
    BOOST_AUTO_TEST_CASE(test_basic_tokens) {

        const std::string test_input("3+3-2*5^2/5*(4-3)");

        const auto& output = test_lexer.tokenise(test_input);

        auto expected_tokens = std::vector<std::unique_ptr<Lexer::Token>>();
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "3"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::Add));
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "3"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::Sub));
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "2"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::Mult));
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "5"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::Exponent));
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "2"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::Divide));
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "5"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::Mult));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::LeftParen));
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "4"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::Sub));
        expected_tokens.emplace_back(std::make_unique<Lexer::LiteralToken>(Lexer::TokenType::Num, "3"));
        expected_tokens.emplace_back(std::make_unique<Lexer::Token>(Lexer::TokenType::RightParen));

        BOOST_TEST(expected_tokens.size() == output.size());

        for (size_t i = 0; i < output.size(); i++) {
            BOOST_TEST(check_token_equal(output[i], expected_tokens[i]));
        }
    }
BOOST_AUTO_TEST_SUITE_END()
