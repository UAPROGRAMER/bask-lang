#ifndef PARSER_HPP
#define PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

class Parser {
private:
    const std::vector<Token>& tokens;
    Token current;
    unsigned long index;

    void advance();

    Token next_token();

    void check(TokenType type);

    std::unique_ptr<AstExpr> parse_func_call();

    std::unique_ptr<AstExpr> parse_factor();

    std::unique_ptr<AstExpr> parse_term();

    std::unique_ptr<AstExpr> parse_expr();

    std::unique_ptr<AstStatement> parse_var_decl();

    std::unique_ptr<AstStatement> parse_var_set();

    std::unique_ptr<AstStatement> parse_func_call_statement();

    std::unique_ptr<AstStatement> parse_statement();
public:
    Parser(const std::vector<Token>& tokens);

    std::vector<std::unique_ptr<AstStatement>> parse();
};

std::vector<std::unique_ptr<AstStatement>> parse(const std::vector<Token>& tokens);

#endif