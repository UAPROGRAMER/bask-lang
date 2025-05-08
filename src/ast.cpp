#include "lib/ast.hpp"

#include <iostream>
#include <utility>

AstInt::AstInt(long value)
: value(value) {}

AstType AstInt::get_type() const {
    return AstType::INT;
}

void AstInt::print() const {
    std::cout << "int(value: " << value << ")";
}

AstFuncCall::AstFuncCall(std::string name, std::vector<std::unique_ptr<AstExpr>> args)
: name(std::move(name)), args(std::move(args)) {}

AstType AstFuncCall::get_type() const {
    return AstType::FUNC_CALL;
}

void AstFuncCall::print() const {
    std::cout << "func_call(name: " << name << ", args: [";
    for (size_t i = 0; i < args.size(); i++) {
        args.at(i)->print();
        if (i != (args.size() - 1))
            std::cout << ", ";
    }
    std::cout << "])";
}

AstName::AstName(std::string name)
: name(std::move(name)) {}

AstType AstName::get_type() const {
    return AstType::NAME;
}

void AstName::print() const {
    std::cout << "name(name: " << name << ")";
}

AstVarDecl::AstVarDecl(std::string name, std::unique_ptr<AstExpr> value)
: name(std::move(name)), value(std::move(value)) {}

AstType AstVarDecl::get_type() const {
    return AstType::VAR_DECL;
}

void AstVarDecl::print() const {
    std::cout << "var_decl(name: " << name << ", value: ";
    value->print();
    std::cout << ")";
}

AstVarSet::AstVarSet(std::string name, std::unique_ptr<AstExpr> value)
: name(std::move(name)), value(std::move(value)) {}

AstType AstVarSet::get_type() const {
    return AstType::VAR_SET;
}

void AstVarSet::print() const {
    std::cout << "var_set(name: " << name << ", value: ";
    value->print();
    std::cout << ")";
}

AstStatementExpr::AstStatementExpr(std::unique_ptr<AstExpr> expr)
: expr(std::move(expr)) {}

AstType AstStatementExpr::get_type() const {
    return AstType::STATEMENT_EXPR;
}

void AstStatementExpr::print() const {
    std::cout << "statement_expr(expr: ";
    expr->print();
    std::cout << ")";
}

void print_asttree(const std::vector<std::unique_ptr<AstStatement>>& asttree) {
    std::cout << "[";
    for (size_t i = 0; i < asttree.size(); i++) {
        asttree.at(i)->print();
        if (i != (asttree.size() - 1))
            std::cout << ", ";
    }
    std::cout << "]\n";
}