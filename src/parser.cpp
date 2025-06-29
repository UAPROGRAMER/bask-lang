#include "lib/parser.hpp"

Parser::Parser(std::vector<Token>& tokens)
: tokens(tokens), current(tokens.at(0)), index(0) {}

void Parser::advance() {
    current = tokens.at(++index);
}

Token& Parser::next_token() {
    return tokens.at(index + 1);
}

void Parser::check(TokenType type) {
    if (current.type != type)
        exit(1);
}

// DO STATEMENTS BRUH

std::unique_ptr<AstDeclaration> Parser::parse_global_const_decl() {
    advance();
    check(TokenType::ID);
    std::string name = current.value;

    advance();
    check(TokenType::EQUAL);
    advance();

    std::unique_ptr<AstExpr> value = parse_expr();

    check(TokenType::SEMI);
    advance();

    return std::make_unique<AstGlobalVarDecl>(std::move(name), std::move(value));
}

std::unique_ptr<AstDeclaration> Parser::parse_global_var_decl() {
    advance();
    check(TokenType::ID);
    std::string name = current.value;

    advance();
    check(TokenType::EQUAL);
    advance();

    std::unique_ptr<AstExpr> value = std::make_unique<AstNull>();

    if (current.type != TokenType::SEMI) {
        value = parse_expr();
        check(TokenType::SEMI);
    }
    advance();

    return std::make_unique<AstGlobalVarDecl>(std::move(name), std::move(value));
}

std::unique_ptr<AstDeclaration> Parser::parse_func_decl() {
    advance();
    check(TokenType::ID);
    std::string name = current.value;

    advance();
    check(TokenType::LPAREN);
    advance();

    bool optional = false;
    std::vector<std::unique_ptr<AstVarDecl>> required_args;
    std::vector<std::unique_ptr<AstVarDecl>> optional_args;

    if (current.type != TokenType::RPAREN)
        while (true) {
            check(TokenType::ID);

            std::string name = current.value;

            advance();

            std::unique_ptr<AstExpr> value = std::make_unique<AstNull>();

            if (current.type == TokenType::EQUAL) {
                optional = true;
                advance();
                value = parse_expr();
            } else {
                if (optional)
                    exit(1);
            }

            if (optional) {
                optional_args.push_back(std::make_unique<AstVarDecl>(std::move(name), std::move(value)));
            } else {
                required_args.push_back(std::make_unique<AstVarDecl>(std::move(name), std::move(value)));
            }

            if (current.type == TokenType::RPAREN)
                break;
            
            check(TokenType::COMA);
            advance();
        }
    
    advance();

    check(TokenType::LCURLY);
    advance();

    std::vector<std::unique_ptr<AstStatement>> code;

    while (current.type != TokenType::RCURLY) {
        code.push_back(parse_statement());
    }

    advance();

    return std::make_unique<AstFuncDecl>(std::move(name), std::move(required_args), std::move(optional_args), std::move(code));
}

std::unique_ptr<AstDeclaration> Parser::parse_declaration() {
    switch (current.type) {
        case TokenType::CONST:
            return parse_global_const_decl();
        case TokenType::VAR:
            return parse_global_var_decl();
        case TokenType::FUNC:
            return parse_func_decl();
        default:
            exit(1);
    }
}

AstProgram Parser::parse() {
    std::vector<std::unique_ptr<AstDeclaration>> declarations;

    while (current.type != TokenType::END)
        declarations.push_back(parse_declaration());

    return AstProgram(std::move(declarations));
}

AstProgram parse(std::vector<Token>& tokens) {
    return Parser(tokens).parse();
}