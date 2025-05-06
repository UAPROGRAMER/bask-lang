#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

enum class TokenType {
    NONE,
    END,
    ID,
    // keywords
    VAR,
    // symbols
    COLUMN,
    SEMI,
    EQUAL,
    PAREN_L,
    PAREN_R,
    // value
    INT
};

const std::unordered_map<std::string, TokenType> TOKEN_KEYWORDS = {
    {"var", TokenType::VAR}
};

class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType type = TokenType::NONE, std::string value = "");

    void print() const;
};

void print_tokens(const std::vector<Token>& tokens);

#endif