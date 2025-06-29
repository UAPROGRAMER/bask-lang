#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <unordered_map>
#include <string>
#include <vector>

enum class TokenType {
    END,
    ID,
    // keywords
    VAR,
    CONST,
    FUNC,
    RETURN,
    // values
    _NULL,
    INT,
    FLOAT,
    STRING,
    // symbols
    EQUAL,
    SEMI,
    COMA,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    LCURLY,
    RCURLY,
};

const std::unordered_map<std::string, TokenType> Keywords = {
    {"null", TokenType::_NULL},
    {"var", TokenType::VAR},
    {"const", TokenType::CONST},
    {"func", TokenType::FUNC},
    {"return", TokenType::RETURN}
};

class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value = "");

    void print() const;
};

void print_tokens(const std::vector<Token>& tokens);

#endif