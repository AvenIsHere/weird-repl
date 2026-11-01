cmake_minimum_required(VERSION 4.3)
project(weird_repl)

set(CMAKE_CXX_STANDARD 20)

add_library(weird_repl_core STATIC
        Repl.cpp
        Repl.h
        Symbol.h
        Token.h
        ASTNode.h
        Lexer.cpp
        Lexer.h
        Parser.cpp
        Parser.h
)

target_include_directories(weird_repl_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(weird_repl main.cpp)
target_link_libraries(weird_repl PRIVATE weird_repl_core)

add_subdirectory(tests)