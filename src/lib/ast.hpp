#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

enum class AstType {
    INT,
    FUNC_CALL,
    NAME,
    VAR_DECL,
    VAR_SET,
    STATEMENT_EXPR
};

class AstNode {
public:
    virtual ~AstNode() = default;

    virtual AstType get_type() const = 0;

    virtual void print() const = 0;
};


// Expresions
class AstExpr : public AstNode {};

class AstInt : public AstExpr {
public:
    long value;

    AstInt(long value);

    AstType get_type() const;

    void print() const;
};

class AstFuncCall : public AstExpr {
public:
    std::string name;
    std::vector<std::unique_ptr<AstExpr>> args;

    AstFuncCall(std::string name, std::vector<std::unique_ptr<AstExpr>> args);

    AstType get_type() const;

    void print() const;
};

class AstName : public AstExpr {
public:
    std::string name;

    AstName(std::string name);

    AstType get_type() const;

    void print() const;
};

// Statements
class AstStatement : public AstNode {};

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

class AstStatementExpr : public AstStatement {
public:
    std::unique_ptr<AstExpr> expr;

    AstStatementExpr(std::unique_ptr<AstExpr> expr);

    AstType get_type() const;

    void print() const;
};

void print_asttree(const std::vector<std::unique_ptr<AstStatement>>& asttree);

#endif