#include "lib/ast.hpp"

#include <iostream>
#include <algorithm>

// NULL

AstNull::AstNull() {}

AstType AstNull::get_type() const {
    return AstType::_NULL;
}

void AstNull::print() const {
    std::cout << "null";
}

// INT

AstInt::AstInt(long value)
: value(value) {}

AstType AstInt::get_type() const {
    return AstType::INT;
}

void AstInt::print() const {
    std::cout << "int(" << value << ")";
}

// FLOAT

AstFloat::AstFloat(double value)
: value(value) {}

AstType AstFloat::get_type() const {
    return AstType::FLOAT;
}

void AstFloat::print() const {
    std::cout << "float(" << value << ")";
}

// STRING

AstString::AstString(std::string value)
: value(std::move(value)) {}

AstType AstString::get_type() const {
    return AstType::STRING;
}

void AstString::print() const {
    std::cout << "string(" << value << ")";
}

// NAME

AstName::AstName(std::string value)
: value(std::move(value)) {}

AstType AstName::get_type() const {
    return AstType::NAME;
}

void AstName::print() const {
    std::cout << "name(" << value << ")";
}

// UNARY OP

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

// BINARY OP

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

// FUNC CALL

AstFuncCall::AstFuncCall(std::unique_ptr<AstExpr> name, std::vector<std::unique_ptr<AstExpr>> args)
: name(std::move(name)), args(std::move(args)) {}

AstType AstFuncCall::get_type() const {
    return AstType::FUNC_CALL;
}

void AstFuncCall::print() const {
    std::cout << "func_call(";
    name->print();
    std::cout << ", [";
    for (size_t i = 0; i < args.size(); i++) {
        args.at(i)->print();
        if (i != args.size() - 1)
            std::cout << ", ";
    }
    std::cout << "])";
}

// CONST DECL

AstConstDecl::AstConstDecl(std::string name, std::unique_ptr<AstExpr> value)
: name(std::move(name)), value(std::move(value)) {}

AstType AstConstDecl::get_type() const {
    return AstType::CONST_DECL;
}

void AstConstDecl::print() const {
    std::cout << "const_decl(" << name << ", ";
    value->print();
    std::cout << ")";
}

// VAR DECL

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

// VAR SET

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

// RETURN

AstReturn::AstReturn(std::unique_ptr<AstExpr> value)
: value(std::move(value)) {}

AstType AstReturn::get_type() const {
    return AstType::RETURN;
}

void AstReturn::print() const {
    std::cout << "return(";
    value->print();
    std::cout << ")";
}

// NO RETURN EXPR

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

// GLOBAL CONST DECL

AstGlobalConstDecl::AstGlobalConstDecl(std::string name, std::unique_ptr<AstExpr> value)
: name(std::move(name)), value(std::move(value)) {}

AstType AstGlobalConstDecl::get_type() const {
    return AstType::GLOBAL_CONST_DECL;
}

void AstGlobalConstDecl::print() const {
    std::cout << "global_const_decl(" << name << ", ";
    value->print();
    std::cout << ")";
}

// GLOBAL VAR DECL

AstGlobalVarDecl::AstGlobalVarDecl(std::string name, std::unique_ptr<AstExpr> value)
: name(std::move(name)), value(std::move(value)) {}

AstType AstGlobalVarDecl::get_type() const {
    return AstType::GLOBAL_CONST_DECL;
}

void AstGlobalVarDecl::print() const {
    std::cout << "global_var_decl(" << name << ", ";
    value->print();
    std::cout << ")";
}

// FUNC DECL

AstFuncDecl::AstFuncDecl(std::string name, std::vector<std::unique_ptr<AstVarDecl>> required_args,
    std::vector<std::unique_ptr<AstVarDecl>> optional_args, std::vector<std::unique_ptr<AstStatement>> code)
: name(std::move(name)), required_args(std::move(required_args)), optional_args(std::move(optional_args)), code(std::move(code)) {}

AstType AstFuncDecl::get_type() const {
    return AstType::FUNC_DECL;
}

void AstFuncDecl::print() const {
    std::cout << "func_decl(" << name << ", [";
    for (size_t i = 0; i < required_args.size(); i++) {
        required_args.at(i)->print();
        if (i != required_args.size() - 1)
            std::cout << ", ";
    }
    std::cout << "], [";
    for (size_t i = 0; i < optional_args.size(); i++) {
        optional_args.at(i)->print();
        if (i != optional_args.size() - 1)
            std::cout << ", ";
    }
    std::cout << "], [";
    for (size_t i = 0; i < code.size(); i++) {
        code.at(i)->print();
        if (i != code.size() - 1)
            std::cout << ", ";
    }
    std::cout << "])";
}

// PROGRAM

AstProgram::AstProgram() {}

AstProgram::AstProgram(std::vector<std::unique_ptr<AstDeclaration>> code)
: code(std::move(code)) {}

void AstProgram::print() const {
    std::cout << "Program([";
    for (size_t i = 0; i < code.size(); i++) {
        code.at(i)->print();
        if (i != code.size() - 1)
            std::cout << ", ";
    }
    std::cout << "])";
}