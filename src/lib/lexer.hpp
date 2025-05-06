#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

class Lexer {
public:
    const std::string& source;
    char current;
    unsigned long index;

    void advance();

    Token word();

    Token number();

    Lexer(const std::string& source);

    Token next();
};

std::vector<Token> tokenize(const std::string& source);

#endif