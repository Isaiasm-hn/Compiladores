#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "lexer.h"
#include "parser.h"

std::vector<TokenInfo> error = {
    _Ident("x"), _OpAssign, _Ident("x")
};

std::vector<TokenInfo> assign = {
    _Ident("x"), _OpAssign, _OpenPar, _Number("175"), _OpAdd, _Number("12"), _ClosePar, _OpMul, _Number("5"), _Semicolon,
    _Ident("y"), _OpAssign, _OpenPar, _Number("175"), _OpSub, _Number("19"), _ClosePar, _OpMul, _Number("3"), _Semicolon,
    _Eof
};

std::vector<TokenInfo> print = {
    _Print, _OpenPar, _Number("10"), _OpAdd, _Number("7"), _ClosePar, _OpMul, _Number("5"), _Semicolon,
    _Print, _OpenPar, _Number("10"), _OpSub, _Number("7"), _ClosePar, _OpMul, _Number("5"), _Semicolon,
    _Eof,
};

std::vector<TokenInfo> functions = {
    _Ident("add"), _OpenPar, _Ident("x"), _ClosePar, _OpAssign, _Ident("x"), _OpAdd, _Ident("y"), _Semicolon,
    _Ident("fact"), _OpenPar, _Number("0"), _ClosePar, _OpAssign, _Number("1"), _Semicolon,
    _Ident("fact"), _OpenPar, _Number("1"), _ClosePar, _OpAssign, _Number("1"), _Semicolon,
    _Ident("fact"), _OpenPar, _Ident("n"), _ClosePar, _OpAssign,
        _OpenPar, _Ident("n"), _OpSub, _Number("1"), _ClosePar, _OpMul, _Ident("n"), _Semicolon,
    _Print, _Ident("fact"), _Semicolon,
    _Eof,
};

bool throwOnError() {
    Lexer l(error);
    Parser p(l); 

    bool success = false;
    try {
        p.parse();
    } catch (...) {
        success = true;
    }
    return success;
}

TEST_CASE("Assign statement") {
    REQUIRE(throwOnError);

    Lexer l(assign);
    Parser p(l);

    REQUIRE_NOTHROW(p.parse());
    REQUIRE(!l.hasTokens());
}

TEST_CASE("Print statement") {
    REQUIRE(throwOnError);

    Lexer l(print);
    Parser p(l);

    REQUIRE_NOTHROW(p.parse());
    REQUIRE(!l.hasTokens());
}

TEST_CASE("Functions") {
    REQUIRE(throwOnError);

    Lexer l(functions);
    Parser p(l);

    REQUIRE_NOTHROW(p.parse());
    REQUIRE(!l.hasTokens());
}
