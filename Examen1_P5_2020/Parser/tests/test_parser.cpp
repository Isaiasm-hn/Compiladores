#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "expr_lexer.h"
#include "expr_parser.h"

std::vector<SymbolInfo> error = {
    std::make_pair(Symbol::Ident, "x"),
    std::make_pair(Symbol::Eof, "EOF")
};

std::vector<SymbolInfo> assign = {
    std::make_pair(Symbol::Ident, "x"),
    std::make_pair(Symbol::OpAssign, "="),
    std::make_pair(Symbol::OpenPar, "("),
    std::make_pair(Symbol::Number, "10"),
    std::make_pair(Symbol::OpAdd, "+"),
    std::make_pair(Symbol::Number, "7"),
    std::make_pair(Symbol::ClosePar, ")"),
    std::make_pair(Symbol::OpMul, "*"),
    std::make_pair(Symbol::Number, "5"),
    std::make_pair(Symbol::Eol, "\\n"),
    std::make_pair(Symbol::Eol, "\\n"),
    std::make_pair(Symbol::Eof, "EOF")
};

std::vector<SymbolInfo> print = {
    std::make_pair(Symbol::Print, "print"),
    std::make_pair(Symbol::OpenPar, "("),
    std::make_pair(Symbol::OpenPar, "("),
    std::make_pair(Symbol::Number, "10"),
    std::make_pair(Symbol::OpAdd, "+"),
    std::make_pair(Symbol::Number, "7"),
    std::make_pair(Symbol::ClosePar, ")"),
    std::make_pair(Symbol::OpMul, "*"),
    std::make_pair(Symbol::Number, "5"),
    std::make_pair(Symbol::ClosePar, ")"),
    std::make_pair(Symbol::Eol, "\\n"),
    std::make_pair(Symbol::Eof, "EOF")
};

std::vector<SymbolInfo> multiple = {
    std::make_pair(Symbol::Ident, "x"),
    std::make_pair(Symbol::OpAssign, "="),
    std::make_pair(Symbol::OpenPar, "("),
    std::make_pair(Symbol::Number, "10"),
    std::make_pair(Symbol::OpAdd, "+"),
    std::make_pair(Symbol::Number, "7"),
    std::make_pair(Symbol::ClosePar, ")"),
    std::make_pair(Symbol::OpMul, "*"),
    std::make_pair(Symbol::Number, "5"),
    std::make_pair(Symbol::Eol, "\\n"),
    std::make_pair(Symbol::Eol, "\\n"),
    std::make_pair(Symbol::Print, "print"),
    std::make_pair(Symbol::OpenPar, "("),
    std::make_pair(Symbol::Ident, "x"),
    std::make_pair(Symbol::ClosePar, ")"),
    std::make_pair(Symbol::Eol, "\\n"),
    std::make_pair(Symbol::Eol, "\\n"),
    std::make_pair(Symbol::Eof, "EOF")
};

bool throwOnError() {
    Lexer l(error);
    std::ostringstream out;
    Parser p(l, out); 

    bool throwException = false;
    try {
        p.parse();
    } catch (...) {
        throwException = true;
    }
    return throwException;
}

TEST_CASE("Assign statement") {
    REQUIRE(throwOnError());

    Lexer l(assign);
    std::ostringstream out;
    Parser p(l, out);

    bool parseSuccess = false;
    try {
        p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    
    std::string str = out.str();
    INFO(str);
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
    CHECK(out.str() == "identifier=(number+number)*number;;");
}

TEST_CASE("Print statement") {
    REQUIRE(throwOnError());

    Lexer l(print);
    std::ostringstream out;
    Parser p(l, out);

    bool parseSuccess = false;
    try {
        p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    std::string str = out.str();
    INFO(str);
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
    CHECK(out.str() == "print((number+number)*number);");
}

TEST_CASE("Assign/Print") {
    REQUIRE(throwOnError());

    Lexer l(multiple);
    std::ostringstream out;
    Parser p(l, out);

    bool parseSuccess = false;
    try {
        p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    std::string str = out.str();
    INFO(str);
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
    CHECK(out.str() == "identifier=(number+number)*number;;print(identifier);;");
}
