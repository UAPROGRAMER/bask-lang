#include "lib/lexer.hpp"
#include "lib/ast.hpp"
//#include "lib/parser.hpp"
//#include "lib/interpreter.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

std::string read_file(char* path) {
    std::ifstream file(path);

    std::stringstream buf;

    buf << file.rdbuf();

    file.close();

    return buf.str();
}

int main(int argc, char* argv[]) {
    /*
    if (argc < 2)
        return 1;

    std::string source = read_file(argv[1]);

    std::vector<Token> tokens = tokenize(source);

    print_tokens(tokens);

    */

    //std::vector<std::unique_ptr<AstStatement>> ast_tree = parse(tokens);

    //run(ast_tree);

    

    return 0;

}