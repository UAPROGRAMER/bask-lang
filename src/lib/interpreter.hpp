#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast.hpp"

#include <stack>
#include <unordered_map>
#include <functional>

namespace build_in_functions {
    long three(const std::vector<long>& args);
    long exitf(const std::vector<long>& args);
}

const std::unordered_map<std::string,
    std::function<long(const std::vector<long>&)>> default_functions = {
    {"three", build_in_functions::three},
    {"exit", build_in_functions::exitf},
};

class Interpreter {
private:
    const std::vector<std::unique_ptr<AstStatement>>& ast_tree;
    std::stack<long> op_stack;
    std::unordered_map<std::string, long> variables;
    std::unordered_map<std::string,
        std::function<long(const std::vector<long>&)>> functions;

    long interprite_int(const std::unique_ptr<AstExpr>& ast_node);
    
    long interprite_var_get(const std::unique_ptr<AstExpr>& ast_node);

    long interprite_unary_op(const std::unique_ptr<AstExpr>& ast_node);

    long interprite_binary_op(const std::unique_ptr<AstExpr>& ast_node);

    long interprite_func_call(const std::unique_ptr<AstExpr>& ast_node);

    long interprite_expr(const std::unique_ptr<AstExpr>& ast_node);

    void interprite_var_decl(const std::unique_ptr<AstStatement>& ast_node);

    void interprite_var_set(const std::unique_ptr<AstStatement>& ast_node);

    void interprite_no_return_expr(const std::unique_ptr<AstStatement>& ast_node);

    void interprite_statement(const std::unique_ptr<AstStatement>& ast_node);
public:
    Interpreter(const std::vector<std::unique_ptr<AstStatement>>& ast_tree);

    void run();
};

void run(const std::vector<std::unique_ptr<AstStatement>>& ast_tree);

#endif