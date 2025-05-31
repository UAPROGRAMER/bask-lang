#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

enum class AstType {
    INT,
    VAR_GET,
    UNARY_OP,
    BINARY_OP,
    FUNC_CALL,
    VAR_DECL,
    VAR_SET,
    NO_RETURN_EXPR,
};

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual AstType get_type() const = 0;
    virtual void print() const = 0;
    virtual size_t get_size() const = 0;
};

class AstExpr : public AstNode {};

class AstInt : public AstExpr {
public:
    long value;

    AstInt(long value);
    AstType get_type() const;
    void print() const;
    size_t get_size() const;
};

class AstVarGet : public AstExpr {
public:
    std::string name;

    AstVarGet(std::string name);
    AstType get_type() const;
    void print() const;
    size_t get_size() const;
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
    size_t get_size() const;
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
    size_t get_size() const;
};

class AstFuncCall : public AstExpr {
public:
    std::string name;
    std::vector<std::unique_ptr<AstExpr>> args;

    AstFuncCall(std::string name, std::vector<std::unique_ptr<AstExpr>> args);
    AstType get_type() const;
    void print() const;
    size_t get_size() const;
};

class AstStatement : public AstNode {};

class AstVarDecl : public AstStatement {
public:
    std::string name;
    std::unique_ptr<AstExpr> value;

    AstVarDecl(std::string name, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
    size_t get_size() const;
};

class AstVarSet : public AstStatement {
public:
    std::string name;
    std::unique_ptr<AstExpr> value;

    AstVarSet(std::string name, std::unique_ptr<AstExpr> value);
    AstType get_type() const;
    void print() const;
    size_t get_size() const;
};

class AstNoReturnExpr : public AstStatement {
public:
    std::unique_ptr<AstExpr> expr;

    AstNoReturnExpr(std::unique_ptr<AstExpr> expr);
    AstType get_type() const;
    void print() const;
    size_t get_size() const;
};

#endif