#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

enum class AstType {
    _NULL,
    INT,
    FLOAT,
    STRING,
    NAME,
    UNARY_OP,
    BINARY_OP,
    FUNC_CALL,
    CONST_DECL,
    VAR_DECL,
    VAR_SET,
    RETURN,
    NO_RETURN_EXPR,
    GLOBAL_CONST_DECL,
    GLOBAL_VAR_DECL,
    FUNC_DECL,
};

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual AstType get_type() const = 0;
    virtual void print() const = 0;
};

// EXPRESIONS

class AstExpr : public AstNode {};

class AstNull : public AstExpr {
public:
    AstNull();
    AstType get_type() const;
    void print() const;
};

class AstInt : public AstExpr {
public:
    long value;

    AstInt(long value);
    AstType get_type() const;
    void print() const;
};

class AstFloat : public AstExpr {
public:
    double value;

    AstFloat(double value);
    AstType get_type() const;
    void print() const;
};

class AstString : public AstExpr {
public:
    std::string value;

    AstString(std::string value);
    AstType get_type() const;
    void print() const;
};

class AstName : public AstExpr {
public:
    std::string value;

    AstName(std::string value);
    AstType get_type() const;
    void print() const;
};

enum class UnaryOpType {
    PLUS_SIGN,
    MINUS_SIGN,
};

class AstUnaryOp : public AstExpr {
public:
    UnaryOpType type;
    std::unique_ptr<AstExpr> value;

    AstUnaryOp(UnaryOpType type, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
};

enum class BinaryOpType {
    ADD,
    SUB,
    MULT,
    DIV,
};

class AstBinaryOp : public AstExpr {
public:
    BinaryOpType type;
    std::unique_ptr<AstExpr> left;
    std::unique_ptr<AstExpr> right;

    AstBinaryOp(BinaryOpType type, std::unique_ptr<AstExpr> left,
        std::unique_ptr<AstExpr> right);
    AstType get_type() const;
    void print() const;
};

class AstFuncCall : public AstExpr {
public:
    std::unique_ptr<AstExpr> name;
    std::vector<std::unique_ptr<AstExpr>> args;

    AstFuncCall(std::unique_ptr<AstExpr> name, std::vector<std::unique_ptr<AstExpr>> args);
    AstType get_type() const;
    void print() const;
};

// STATEMENTS

class AstStatement : public AstNode {};

class AstConstDecl : public AstStatement {
public:
    std::string name;
    std::unique_ptr<AstExpr> value;

    AstConstDecl(std::string name, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
};

class AstVarDecl : public AstStatement {
public:
    std::string name;
    std::unique_ptr<AstExpr> value;

    AstVarDecl(std::string name, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
};

class AstVarSet : public AstStatement {
public:
    std::string name;
    std::unique_ptr<AstExpr> value;

    AstVarSet(std::string name, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
};

class AstReturn : public AstStatement {
public:
    std::unique_ptr<AstExpr> value;

    AstReturn(std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
};

class AstNoReturnExpr : public AstStatement {
public:
    std::unique_ptr<AstExpr> expr;

    AstNoReturnExpr(std::unique_ptr<AstExpr> expr);
    AstType get_type() const;
    void print() const;
};

// DECLARATIONS

class AstDeclaration : public AstNode {};

class AstGlobalConstDecl : public AstDeclaration {
public:
    std::string name;
    std::unique_ptr<AstExpr> value;

    AstGlobalConstDecl(std::string name, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
};

class AstGlobalVarDecl : public AstDeclaration {
public:
    std::string name;
    std::unique_ptr<AstExpr> value;

    AstGlobalVarDecl(std::string name, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
};

class AstFuncDecl : public AstDeclaration {
public:
    std::string name;
    std::vector<std::unique_ptr<AstVarDecl>> required_args;
    std::vector<std::unique_ptr<AstVarDecl>> optional_args;
    std::vector<std::unique_ptr<AstStatement>> code;

    AstFuncDecl(std::string name, std::vector<std::unique_ptr<AstVarDecl>> required_args,
        std::vector<std::unique_ptr<AstVarDecl>> optional_args, std::vector<std::unique_ptr<AstStatement>> code);
    AstType get_type() const;
    void print() const;
};

// PROGRAM

class AstProgram {
public:
    std::vector<std::unique_ptr<AstDeclaration>> code;

    AstProgram();
    AstProgram(std::vector<std::unique_ptr<AstDeclaration>> code);
    void print() const;
};

#endif