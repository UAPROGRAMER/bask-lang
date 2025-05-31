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
    // values
    INT,
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
};

const std::unordered_map<std::string, TokenType> Keywords = {
    {"var", TokenType::VAR}
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