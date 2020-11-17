#ifndef __EXPR_TOKENS_H__
#define __EXPR_TOKENS_H__

enum class Token {
    ClosePar,
    OpenPar,
    Number,
    OpSub,
    Eof,
    OpAdd,
    Ident,
    OpMul,
    OpDiv,
};

#endif