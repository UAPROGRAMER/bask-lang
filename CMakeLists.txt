cmake_minimum_required(VERSION 3.10)
project(bask-lang)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(bask src/main.cpp src/token.cpp src/lexer.cpp src/ast.cpp) #src/parser.cpp src/interpreter.cpp)