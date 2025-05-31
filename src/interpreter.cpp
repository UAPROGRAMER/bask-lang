#include "lib/interpreter.hpp"

namespace build_in_functions {
    long three(const std::vector<long>& args) {
        return 3;
    }

    long exitf(const std::vector<long>& args) {
        if (args.size() != 1)
            exit(1);
        exit(args.at(0));
    }
}

Interpreter::Interpreter(const std::vector<std::unique_ptr<AstStatement>>& ast_tree)
: ast_tree(ast_tree), functions(default_functions) {}

long Interpreter::interprite_int(const std::unique_ptr<AstExpr>& ast_node) {
    return static_cast<AstInt*>(ast_node.get())->value;
}
    
long Interpreter::interprite_var_get(const std::unique_ptr<AstExpr>& ast_node) {
    const AstVarGet* ptr = static_cast<AstVarGet*>(ast_node.get());
    std::string name = ptr->name;
    if (variables.find(name) == variables.end())
        exit(1);
    return variables.at(name);
}

long Interpreter::interprite_unary_op(const std::unique_ptr<AstExpr>& ast_node) {
    const AstUnaryOp* ptr = static_cast<AstUnaryOp*>(ast_node.get());
    switch (ptr->type) {
        case UnaryOpType::PLUS_SIGN:
            return interprite_expr(ptr->value);
        case UnaryOpType::MINUS_SIGN:
            return -interprite_expr(ptr->value);
        default:
            exit(1);
    }
}

long Interpreter::interprite_binary_op(const std::unique_ptr<AstExpr>& ast_node) {
    const AstBinaryOp* ptr = static_cast<AstBinaryOp*>(ast_node.get());
    switch (ptr->type) {
        case BinaryOpType::ADD:
            return interprite_expr(ptr->left) + interprite_expr(ptr->right);
        case BinaryOpType::SUB:
            return interprite_expr(ptr->left) - interprite_expr(ptr->right);
        case BinaryOpType::MULT:
            return interprite_expr(ptr->left) * interprite_expr(ptr->right);
        case BinaryOpType::DIV:
            return interprite_expr(ptr->left) / interprite_expr(ptr->right);
        default:
            exit(1);
    }
}

long Interpreter::interprite_func_call(const std::unique_ptr<AstExpr>& ast_node) {
    const AstFuncCall* ptr = static_cast<AstFuncCall*>(ast_node.get());

    std::string name = ptr->name;
    if (functions.find(name) == functions.end())
        exit(1);

    std::vector<long> args;
    for (const auto& arg : ptr->args)
        args.push_back(interprite_expr(arg));
    
    return functions.at(name)(args);
}

long Interpreter::interprite_expr(const std::unique_ptr<AstExpr>& ast_node) {
    switch (ast_node->get_type()) {
        case AstType::INT:
            return interprite_int(ast_node);
        case AstType::VAR_GET:
            return interprite_var_get(ast_node);
        case AstType::UNARY_OP:
            return interprite_unary_op(ast_node);
        case AstType::BINARY_OP:
            return interprite_binary_op(ast_node);
        case AstType::FUNC_CALL:
            return interprite_func_call(ast_node);
        default:
            exit(1);
    }
}

void Interpreter::interprite_var_decl(const std::unique_ptr<AstStatement>& ast_node) {
    const AstVarDecl* ptr = static_cast<AstVarDecl*>(ast_node.get());
    std::string name = ptr->name;
    if (variables.find(name) != variables.end())
        exit(1);
    variables[name] = interprite_expr(ptr->value);
}

void Interpreter::interprite_var_set(const std::unique_ptr<AstStatement>& ast_node) {
    const AstVarSet* ptr = static_cast<AstVarSet*>(ast_node.get());
    std::string name = ptr->name;
    if (variables.find(name) == variables.end())
        exit(1);
    variables[name] = interprite_expr(ptr->value);
}

void Interpreter::interprite_no_return_expr(const std::unique_ptr<AstStatement>& ast_node) {
    interprite_expr(static_cast<AstNoReturnExpr*>(ast_node.get())->expr);
}

void Interpreter::interprite_statement(const std::unique_ptr<AstStatement>& ast_node) {
    switch (ast_node->get_type()) {
        case AstType::VAR_DECL:
            return interprite_var_decl(ast_node);
        case AstType::VAR_SET:
            return interprite_var_set(ast_node);
        case AstType::NO_RETURN_EXPR:
            return interprite_no_return_expr(ast_node);
        default:
            exit(1);
    }
}

void Interpreter::run() {
    for (const auto& ast_node : ast_tree)
        interprite_statement(ast_node);
}

void run(const std::vector<std::unique_ptr<AstStatement>>& ast_tree) {
    Interpreter(ast_tree).run();
}