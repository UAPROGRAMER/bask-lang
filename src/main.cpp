#include "lib/lexer.hpp"

#include <fstream>

std::string read_file(char* path) {
    std::ifstream file(path);

    std::stringstream buf;

    buf << file.rdbuf();

    return buf.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        return 1;

    std::string source = read_file(argv[1]);

    std::vector<Token> tokens = tokenize(source);

    print_tokens(tokens);
}