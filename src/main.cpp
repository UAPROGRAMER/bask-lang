#include "lib/lexer.hpp"
#include "lib/ast.hpp"

#include <fstream>
#include <sstream>

std::string read_file(char* path) {
    std::ifstream file(path);

    std::stringstream buf;

    buf << file.rdbuf();

    return buf.str();
}

int main(int argc, char* argv[]) {
/*  if (argc < 2)
        return 1;

    std::string source = read_file(argv[1]);

    std::vector<Token> tokens = tokenize(source);

    print_tokens(tokens); */

    std::vector<std::unique_ptr<AstStatement>> asttree;

    asttree.push_back(std::make_unique<AstVarDecl>("name", std::make_unique<AstInt>(10)));

    asttree.push_back(std::make_unique<AstVarSet>("name", std::make_unique<AstInt>(2)));

    std::vector<std::unique_ptr<AstExpr>> args;

    args.push_back(std::make_unique<AstName>("name"));

    asttree.push_back(std::make_unique<AstStatementExpr>(std::make_unique<AstFuncCall>("exit", std::move(args))));
    
    print_asttree(asttree);
}