#ifndef _PARSER_H
#define _PARSER_H

#include <iosfwd>
#include "expr_lexer.h"

class Parser
{
public:
    Parser(Lexer& lexer, std::ostream& out): lexer(lexer), out(out)
    {}

    int parse();

private:
    Lexer& lexer;
    std::ostream& out;
};

#endif
