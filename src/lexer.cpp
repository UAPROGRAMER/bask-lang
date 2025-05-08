#include "lib/lexer.hpp"

#include <sstream>

Lexer::Lexer(const std::string& source)
: source(source), current('\0'), index(-1) {
    advance();
}

void Lexer::advance() {
    current = ++index < source.size() ? source.at(index) : '\0';
}

Token Lexer::word() {
    std::stringstream buf;
    while (std::isalnum(current) || current == '_') {
        buf << current;
        advance();
    }
    std::string value = buf.str();

    TokenType type = TokenType::ID;

    if (TOKEN_KEYWORDS.find(value) != TOKEN_KEYWORDS.end()) {
        type = TOKEN_KEYWORDS.at(value);
        return Token(type);
    }

    return Token(type, value);
}

Token Lexer::number() {
    std::stringstream buf;
    while (std::isdigit(current)) {
        buf << current;
        advance();
    }
    return Token(TokenType::INT, buf.str());
}

Token Lexer::next() {
    while (std::isspace(current))
        advance();
    
    if (std::isalpha(current) || current == '_')
        return word();
    
    if (std::isdigit(current))
        return number();
    
    TokenType type;
    switch (current) {
    case '\0':
        type = TokenType::END;
        break;
    case ':':
        type = TokenType::COLUMN;
        break;
    case ';':
        type = TokenType::SEMI;
        break;
    case '=':
        type = TokenType::EQUAL;
        break;
    case '(':
        type = TokenType::PAREN_L;
        break;
    case ')':
        type = TokenType::PAREN_R;
        break;
    default:
        exit(1);
    }

    advance();

    return Token(type);
}

std::vector<Token> tokenize(const std::string& source) {
    std::vector<Token> tokens;
    Lexer lexer(source);
    while (lexer.current != '\0')
        tokens.push_back(lexer.next());
    tokens.push_back(Token(TokenType::END));
    return tokens;
}