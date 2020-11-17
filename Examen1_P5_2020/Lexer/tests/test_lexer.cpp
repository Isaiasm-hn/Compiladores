#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cstring>
#include <memory>
#include <sstream>

#include "doctest.h"
#include "expr_lexer.h"

const char *test1 = "45984735 + 1432654372 - 203495349085";
const char *test2 = "$_variable_1 + $_variable_2 - ___very_long_variable_name_with_many_underscores__";
const char *test3 = "(0.56 + 1.54) * (10.34 + 333.789) / 3.141592653589793238462643383279502884197169399375105820974944592307816406286";
const char *test_lc =
    "/! Line comment\n"
    "45984735 /! Line Comment\n"
    "+ /! Line Comment\n"
    "1432654372 /! Line Comment\n"
    "/!";

const char *test_bc1 =
    "/!! Block comment !!/\n"
    "/!! Block comment !!/ 45984735 /!! Block comment !!/ + /!! Block comment !!/ 1432654372\n";

const char *test_bc2 =
    "/!! Block comment !!! \n"
    " Block comment !!! /// !!/45984735/!! Block comment !!! \n"
    " Block comment !!! /// !!/ + 1432654372/!! Block comment !!! \n"
    " Block comment !!! /// !!/";

doctest::String toString(Token tk)
{
    switch (tk)
    {
        case Token::ClosePar:
            return "ClosePar";
        case Token::Eof:
            return "Eof";
        case Token::Ident:
            return "Ident";
        case Token::Number:
            return "Number";
        case Token::OpAdd:
            return "OpAdd";
        case Token::OpDiv:
            return "OpDiv";
        case Token::OpMul:
            return "OpMul";
        case Token::OpSub:
            return "OpSub";
        case Token::OpenPar:
            return "OpenPar";
        default:
            return "Unknown";
    }
}

TEST_CASE("Simple expr with integer numbers")
{
    std::istringstream in;

    in.str(test1);
    ExprLexer l(in);

    Token tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "45984735");

    tk = l.getNextToken();
    CHECK(tk == Token::OpAdd);
    CHECK(l.getText() == "+");

    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "1432654372");

    tk = l.getNextToken();
    CHECK(tk == Token::OpSub);
    CHECK(l.getText() == "-");

    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "203495349085");

    tk = l.getNextToken();
    CHECK(tk == Token::Eof);
}

TEST_CASE("Simple expr with variables")
{
    std::istringstream in;

    in.str(test2);
    ExprLexer l(in);

    Token tk = l.getNextToken();
    CHECK(tk == Token::Ident);
    CHECK(l.getText() == "$_variable_1");

    tk = l.getNextToken();
    CHECK(tk == Token::OpAdd);
    CHECK(l.getText() == "+");

    tk = l.getNextToken();
    CHECK(tk == Token::Ident);
    CHECK(l.getText() == "$_variable_2");

    tk = l.getNextToken();
    CHECK(tk == Token::OpSub);
    CHECK(l.getText() == "-");

    tk = l.getNextToken();
    CHECK(tk == Token::Ident);
    CHECK(l.getText() == "___very_long_variable_name_with_many_underscores__");

    tk = l.getNextToken();
    CHECK(tk == Token::Eof);
}

TEST_CASE("Complex expression with real numbers")
{
    std::istringstream in;

    in.str(test3);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK(tk == Token::OpenPar);
    CHECK(l.getText() == "(");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "0.56");
    tk = l.getNextToken();
    CHECK(tk == Token::OpAdd);
    CHECK(l.getText() == "+");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "1.54");
    tk = l.getNextToken();
    CHECK(tk == Token::ClosePar);
    CHECK(l.getText() == ")");
    tk = l.getNextToken();
    CHECK(tk == Token::OpMul);
    CHECK(l.getText() == "*");

    tk = l.getNextToken();
    CHECK(tk == Token::OpenPar);
    CHECK(l.getText() == "(");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "10.34");
    tk = l.getNextToken();
    CHECK(tk == Token::OpAdd);
    CHECK(l.getText() == "+");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "333.789");
    tk = l.getNextToken();
    CHECK(tk == Token::ClosePar);
    CHECK(l.getText() == ")");
    tk = l.getNextToken();
    CHECK(tk == Token::OpDiv);
    CHECK(l.getText() == "/");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "3.141592653589793238462643383279502884197169399375105820974944592307816406286");
    tk = l.getNextToken();
    CHECK(tk == Token::Eof);
}


TEST_CASE("Line comments")
{
    std::istringstream in;

    in.str(test_lc);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK(tk == Token::Number);
    CHECK(l.getText() == "45984735");
    tk = l.getNextToken();
    CHECK(tk == Token::OpAdd);
    CHECK(l.getText() == "+");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "1432654372");
    tk = l.getNextToken();
    CHECK(tk == Token::Eof);
}

TEST_CASE("Block comments 1")
{
    std::istringstream in;

    in.str(test_bc1);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK(tk == Token::Number);
    CHECK(l.getText() == "45984735");
    tk = l.getNextToken();
    CHECK(tk == Token::OpAdd);
    CHECK(l.getText() == "+");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "1432654372");
    tk = l.getNextToken();
    CHECK(tk == Token::Eof);
}

TEST_CASE("Block comments 2")
{
    std::istringstream in;

    in.str(test_bc2);
    ExprLexer l(in);
    Token tk = l.getNextToken();

    CHECK(tk == Token::Number);
    CHECK(l.getText() == "45984735");
    tk = l.getNextToken();
    CHECK(tk == Token::OpAdd);
    CHECK(l.getText() == "+");
    tk = l.getNextToken();
    CHECK(tk == Token::Number);
    CHECK(l.getText() == "1432654372");
    tk = l.getNextToken();
    CHECK(tk == Token::Eof);
}
