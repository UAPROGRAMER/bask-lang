#include "lib/parser.hpp"

Parser::Parser(const std::vector<Token>& tokens)
: tokens(tokens), current(tokens.at(0)), index(0) {}

void Parser::advance() {
    current = tokens.at(++index);
}

Token Parser::next_token() {
    return tokens.at(index + 1);
}

void Parser::check(TokenType type) {
    if (current.type != type)
        exit(1);
}

std::unique_ptr<AstExpr> Parser::parse_func_call() {
    check(TokenType::ID);
    std::string name = current.value;
    advance();
    check(TokenType::LPAREN);
    advance();
    
    std::vector<std::unique_ptr<AstExpr>> args;
    
    if (current.type == TokenType::RPAREN) {
        advance();
        return std::make_unique<AstFuncCall>(std::move(name), std::move(args));
    }

    do {
        args.push_back(parse_expr());
    } while (current.type == TokenType::COMA);

    check(TokenType::RPAREN);
    advance();

    return std::make_unique<AstFuncCall>(std::move(name), std::move(args));
}

std::unique_ptr<AstExpr> Parser::parse_factor() {
    std::unique_ptr<AstExpr> result;

    switch (current.type) {
        case TokenType::LPAREN:
            advance();
            result = parse_expr();
            check(TokenType::RPAREN);
            advance();
            break;
        case TokenType::INT:
            result = std::make_unique<AstInt>(std::stol(current.value));
            advance();
            break;
        case TokenType::ID:
            if (next_token().type == TokenType::LPAREN)
                result = parse_func_call();
            else {
                result = std::make_unique<AstVarGet>(current.value);
                advance();
            }
            break;
        case TokenType::PLUS:
            advance();
            result = std::make_unique<AstUnaryOp>(UnaryOpType::PLUS_SIGN, parse_factor());
            break;
        case TokenType::MINUS:
            advance();
            result = std::make_unique<AstUnaryOp>(UnaryOpType::MINUS_SIGN, parse_factor());
            break;
        default:
            exit(1);
    }

    return result;
}

std::unique_ptr<AstExpr> Parser::parse_term() {
    auto result = parse_factor();

    while (current.type == TokenType::MULTIPLY || current.type == TokenType::DIVIDE) {
        switch (current.type) {
            case TokenType::MULTIPLY:
                advance();
                result = std::make_unique<AstBinaryOp>(BinaryOpType::MULT, std::move(result), parse_factor());
                break;
            case TokenType::DIVIDE:
                advance();
                result = std::make_unique<AstBinaryOp>(BinaryOpType::DIV, std::move(result), parse_factor());
                break;
        }
    }

    return result;
}

std::unique_ptr<AstExpr> Parser::parse_expr() {
    auto result = parse_term();

    while (current.type == TokenType::PLUS || current.type == TokenType::MINUS) {
        switch (current.type) {
            case TokenType::PLUS:
                advance();
                result = std::make_unique<AstBinaryOp>(BinaryOpType::ADD, std::move(result), parse_term());
                break;
            case TokenType::MINUS:
                advance();
                result = std::make_unique<AstBinaryOp>(BinaryOpType::SUB, std::move(result), parse_term());
                break;
        }
    }

    return result;
}

std::unique_ptr<AstStatement> Parser::parse_var_decl() {
    check(TokenType::VAR);
    advance();
    check(TokenType::ID);
    std::string name = current.value;
    advance();
    check(TokenType::EQUAL);
    advance();
    std::unique_ptr<AstExpr> value = parse_expr();
    check(TokenType::SEMI);
    advance();
    return std::make_unique<AstVarDecl>(std::move(name), std::move(value));
}
#include <iostream>
std::unique_ptr<AstStatement> Parser::parse_var_set() {
    check(TokenType::ID);
    std::string name = current.value;
    advance();
    check(TokenType::EQUAL);
    advance();
    std::unique_ptr<AstExpr> value = parse_expr();
    check(TokenType::SEMI);
    advance();
    return std::make_unique<AstVarSet>(std::move(name), std::move(value));
}

std::unique_ptr<AstStatement> Parser::parse_func_call_statement() {
    std::unique_ptr<AstStatement> result = std::make_unique<AstNoReturnExpr>(parse_func_call());
    check(TokenType::SEMI);
    advance();
    return result;
}

std::unique_ptr<AstStatement> Parser::parse_statement() {
    switch (current.type) {
        case TokenType::ID:
            if (next_token().type == TokenType::LPAREN)
                return parse_func_call_statement();
            return parse_var_set();
        case TokenType::VAR:
            return parse_var_decl();
        default:
            exit(1); 
    }
}

std::vector<std::unique_ptr<AstStatement>> Parser::parse() {
    std::vector<std::unique_ptr<AstStatement>> ast_tree;
    while (current.type != TokenType::END)
        ast_tree.push_back(parse_statement());
    return ast_tree;
}

std::vector<std::unique_ptr<AstStatement>> parse(const std::vector<Token>& tokens) {
    return Parser(tokens).parse();
}