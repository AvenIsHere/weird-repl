//
// Created by aven on 30/10/2026.
//

#ifndef WEIRD_REPL_REPL_H
#define WEIRD_REPL_REPL_H
#include "Lexer.h"


class Repl {

    Lexer::Lexer lexer;

public:

    Repl();

    void loop();

};


#endif //WEIRD_REPL_REPL_H
