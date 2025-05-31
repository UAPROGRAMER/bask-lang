#include "lib/ast.hpp"

#include <iostream>
#include <algorithm>

AstInt::AstInt(long value)
: value(value) {}

AstType AstInt::get_type() const {
    return AstType::INT;
}

void AstInt::print() const {
    std::cout << "int(" << value << ")";
}

size_t AstInt::get_size() const {
    return sizeof(AstInt);
}

AstVarGet::AstVarGet(std::string name) : name(std::move(name)) {};

AstType AstVarGet::get_type() const {
    return AstType::VAR_GET;
}

void AstVarGet::print() const {
    std::cout << "var_get(" << name << ")";
}

size_t AstVarGet::get_size() const {
    return sizeof(AstVarGet);
}

AstUnaryOp::AstUnaryOp(UnaryOpType type, std::unique_ptr<AstExpr> value)
: type(type), value(std::move(value)) {}

AstType AstUnaryOp::get_type() const {
    return AstType::UNARY_OP;
}

void AstUnaryOp::print() const {
    std::cout << "unary_op(" << static_cast<unsigned short>(type) << ", ";
    value->print();
    std::cout << ")";
}

size_t AstUnaryOp::get_size() const {
    return sizeof(AstUnaryOp) + value->get_size();
}

AstBinaryOp::AstBinaryOp(BinaryOpType type, std::unique_ptr<AstExpr> left,
    std::unique_ptr<AstExpr> right)
: type(type), left(std::move(left)), right(std::move(right)) {}

AstType AstBinaryOp::get_type() const {
    return AstType::BINARY_OP;
}

void AstBinaryOp::print() const {
    std::cout << "binary_op(" << static_cast<unsigned short>(type) << ", ";
    left->print();
    std::cout << ", ";
    right->print();
    std::cout << ")";
}

size_t AstBinaryOp::get_size() const {
    return sizeof(AstBinaryOp) + left->get_size() + right->get_size();
}

AstFuncCall::AstFuncCall(std::string name, std::vector<std::unique_ptr<AstExpr>> args)
: name(std::move(name)), args(std::move(args)) {}

AstType AstFuncCall::get_type() const {
    return AstType::FUNC_CALL;
}

void AstFuncCall::print() const {
    std::cout << "func_call(" << name << ", [";
    for (size_t i = 0; i < args.size(); i++) {
        args.at(i)->print();
        if (i != args.size() - 1)
            std::cout << ", ";
    }
    std::cout << "])";
}

size_t AstFuncCall::get_size() const {
    size_t size = sizeof(AstFuncCall) + args.size() * sizeof(std::unique_ptr<AstExpr>);
    for (const auto& expr : args)
        size += expr->get_size();
    return size;
}

AstVarDecl::AstVarDecl(std::string name, std::unique_ptr<AstExpr> value)
: name(std::move(name)), value(std::move(value)) {}

AstType AstVarDecl::get_type() const {
    return AstType::VAR_DECL;
}

void AstVarDecl::print() const {
    std::cout << "var_decl(" << name << ", ";
    value->print();
    std::cout << ")";
}

size_t AstVarDecl::get_size() const {
    return sizeof(AstVarDecl) + value->get_size();
}

AstVarSet::AstVarSet(std::string name, std::unique_ptr<AstExpr> value)
: name(std::move(name)), value(std::move(value)) {}

AstType AstVarSet::get_type() const {
    return AstType::VAR_SET;
}

void AstVarSet::print() const {
    std::cout << "var_set(" << name << ", ";
    value->print();
    std::cout << ")";
}

size_t AstVarSet::get_size() const {
    return sizeof(AstVarSet) + value->get_size();
}

AstNoReturnExpr::AstNoReturnExpr(std::unique_ptr<AstExpr> expr)
: expr(std::move(expr)) {}

AstType AstNoReturnExpr::get_type() const {
    return AstType::NO_RETURN_EXPR;
}

void AstNoReturnExpr::print() const {
    std::cout << "no_return_expr(";
    expr->print();
    std::cout << ")";
}

size_t AstNoReturnExpr::get_size() const {
    return sizeof(AstNoReturnExpr) + expr->get_size();
}