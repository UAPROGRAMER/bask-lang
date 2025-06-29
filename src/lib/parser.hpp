#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

class Parser {
private:
    std::vector<Token>& tokens;
    Token& current;
    unsigned long index;

    void advance();

    Token& next_token();

    void check(TokenType type);

    std::unique_ptr<AstExpr> parse_factor();

    std::unique_ptr<AstExpr> parse_term();

    std::unique_ptr<AstExpr> parse_expr();

    std::unique_ptr<AstStatement> parse_const_decl();

    std::unique_ptr<AstStatement> parse_var_decl();

    std::unique_ptr<AstStatement> parse_var_set();

    std::unique_ptr<AstStatement> parse_return();

    std::unique_ptr<AstStatement> parse_statement();

    std::unique_ptr<AstDeclaration> parse_global_const_decl();

    std::unique_ptr<AstDeclaration> parse_global_var_decl();

    std::unique_ptr<AstDeclaration> parse_func_decl();

    std::unique_ptr<AstDeclaration> parse_declaration();
public:
    Parser(std::vector<Token>& tokens);

    AstProgram parse();
};

AstProgram parse(std::vector<Token>& tokens);

#endif