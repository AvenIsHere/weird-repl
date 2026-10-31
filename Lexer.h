//
// Created by aven on 30/10/2026.
//

#ifndef WEIRD_REPL_LEXER_H
#define WEIRD_REPL_LEXER_H
#include <memory>
#include <optional>
#include <vector>

#include "Token.h"

namespace Lexer {
    class Lexer {

        size_t char_index;

        std::string get_num(const std::string& input);
        std::string get_ident(const std::string &input);
        [[nodiscard]] std::string get_str(const std::string &input, char quote_char);
        [[nodiscard]] std::optional<char> get_next_token(std::string input) const;

        std::unique_ptr<Token> parse_token(const std::string &input);

    public:

        Lexer();

        std::vector<std::unique_ptr<Token>> tokenise(const std::string& input);

    };
}


#endif //WEIRD_REPL_LEXER_H
