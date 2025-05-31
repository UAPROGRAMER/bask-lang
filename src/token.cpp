#include "lib/token.hpp"

#include <iostream>
#include <utility>

Token::Token(TokenType type, std::string value)
: type(type), value(std::move(value)) {}

void Token::print() const {
    std::cout << "(" << static_cast<unsigned short>(type);
    if (value != "")
        std::cout << ", " << value;
    std::cout << ")";
}

void print_tokens(const std::vector<Token>& tokens) {
    std::cout << "[";
    for (size_t i = 0; i < tokens.size(); i++) {
        tokens.at(i).print();
        if (i != (tokens.size() - 1))
            std::cout << ", ";
    }
    std::cout << "]\n";
}