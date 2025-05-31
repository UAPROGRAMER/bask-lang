#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

class Lexer {
private:
    const std::string& source;
    char current;
    unsigned long index;

    void advance();

    void skip();

    Token next();

    Token word();

    Token num();
public:
    Lexer(const std::string& source);

    std::vector<Token> tokenize();
};

std::vector<Token> tokenize(const std::string& source);

#endif