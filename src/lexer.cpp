#include "lib/lexer.hpp"

#include <sstream>
#include <iostream>

Lexer::Lexer(const std::string& source)
: source(source), current('\0'), index(-1) {
    advance();
}

void Lexer::advance() {
    current = (++index < source.size()) ? source.at(index) : '\0';
}

void Lexer::skip() {
    if (current == '\0')
        return;
    
    while (std::isspace(current))
        advance();
    
    if (current == '#') {
        while (current != '\n') {
            if (current == '\0')
                return;
            advance();
        }
        return skip();
    }

    if (current == '\'') {
        advance();
        while (current != '\'') {
            if (current == '\0')
                exit(1);
            advance();
        }
        advance();
        return skip();
    }
}

Token Lexer::next() {
    skip();
    
    if (std::isalpha(current) || current == '_')
        return word();
    
    if (std::isdigit(current))
        return num();
    
    if (current == '"')
        return string();

    TokenType type;
    switch (current) {
        case '\0':
            type = TokenType::END;
            break;
        case '=':
            type = TokenType::EQUAL;
            break;
        case ';':
            type = TokenType::SEMI;
            break;
        case ',':
            type = TokenType::COMA;
            break;
        case '+':
            type = TokenType::PLUS;
            break;
        case '-':
            type = TokenType::MINUS;
            break;
        case '*':
            type = TokenType::MULTIPLY;
            break;
        case '/':
            type = TokenType::DIVIDE;
            break;
        case '(':
            type = TokenType::LPAREN;
            break;
        case ')':
            type = TokenType::RPAREN;
            break;
        case '{':
            type = TokenType::LCURLY;
            break;
        case '}':
            type = TokenType::RCURLY;
            break;
        default:
            std::cerr << "ERROR::LEXER::UNEXPECTED_CHAR\n";
            std::cerr << "character = '" << current << "'\n";
            exit(1);
    }

    advance();

    return Token(type);
}

Token Lexer::word() {
    std::stringstream buf;

    while (std::isalnum(current) || current == '_') {
        buf << current;
        advance();
    }

    std::string value = buf.str();

    if (Keywords.find(value) != Keywords.end())
        return Token(Keywords.at(value));

    return Token(TokenType::ID, value);
}

Token Lexer::string() {
    advance();
    std::stringstream buf;

    while (current != '"') {
        if (current == '\0')
            exit(1);

        if (current == '\\') {
            advance();
            switch (current) {
                case '\0':
                    exit(1);
                case 'n':
                    current = '\n';
                    break;
                default:
                    break;
            }
        }

        buf << current;
        advance();
    }

    advance();

    return Token(TokenType::STRING, buf.str());
}

Token Lexer::num() {
    std::stringstream buf;
    bool dot = false;

    while (std::isdigit(current) || current == '.') {
        if (current == '.')
            if (dot)
                exit(1);
            else
                dot = true;
        buf << current;
        advance();
    }

    if (dot)
        return Token(TokenType::FLOAT, buf.str());
    
    return Token(TokenType::INT, buf.str());
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token = next();

    while (token.type != TokenType::END) {
        tokens.push_back(token);
        token = next();
    }

    tokens.push_back(token);

    return tokens;
}

std::vector<Token> tokenize(const std::string& source) {
    return Lexer(source).tokenize();
}