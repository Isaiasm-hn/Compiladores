#include "expr_lexer.h"

enum class State {
    start_q0,
    Number_q0,
    Number_q1,
    Number_q2,
    Number_q3,
    arith_q0,
    arith_q1,
    arith_q2,
    arith_q3,
    arith_q4,
    arith_q5,
    arith_q6,
    identifier_q0,
    identifier_q1,
    identifier_q2,
    identifier_q4,
    identifier_q5,
};

Token ExprLexer::getNextToken()
{
    text = "";
    State state = State::start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // start
            case State::start_q0:
                if ((ch == '\n') || (ch == ' ')) {
                    state = State::start_q0;
                    ch = getNextChar();
                }
                else if (ch == EOF) {
                    text += ch;
                    return Token::Eof;
                }
                else {
                    // Trying next automaton 'Number
                    state = State::Number_q0;
                }
                break;
            // Number
            case State::Number_q0:
                if (ch == EOF) {
                    text += ch;
                    return Token::Eof;
                }
                else if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Number_q1;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'arith
                    state = State::arith_q0;
                }
                break;
            case State::Number_q1:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Number_q1;
                    ch = getNextChar();
                }
                else if (ch == '.') {
                    text += ch;
                    state = State::Number_q2;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            case State::Number_q2:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Number_q3;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'arith
                    state = State::arith_q0;
                }
                break;
            case State::Number_q3:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Number_q3;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            // arith
            case State::arith_q0:
                if (ch == ')') {
                    text += ch;
                    state = State::arith_q6;
                    ch = getNextChar();
                }
                else if (ch == '*') {
                    text += ch;
                    state = State::arith_q3;
                    ch = getNextChar();
                }
                else if (ch == '/') {
                    text += ch;
                    state = State::arith_q4;
                    ch = getNextChar();
                }
                else if (ch == '-') {
                    text += ch;
                    state = State::arith_q2;
                    ch = getNextChar();
                }
                else if (ch == '(') {
                    text += ch;
                    state = State::arith_q5;
                    ch = getNextChar();
                }
                else if (ch == EOF) {
                    text += ch;
                    return Token::Eof;
                }
                else if (ch == '+') {
                    text += ch;
                    state = State::arith_q1;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'identifier
                    state = State::identifier_q0;
                }
                break;
            case State::arith_q1:
                ungetChar(ch);
                return Token::OpAdd;
                break;
            case State::arith_q2:
                ungetChar(ch);
                return Token::OpSub;
                break;
            case State::arith_q3:
                ungetChar(ch);
                return Token::OpMul;
                break;
            case State::arith_q4:
                ungetChar(ch);
                return Token::OpDiv;
                break;
            case State::arith_q5:
                ungetChar(ch);
                return Token::OpenPar;
                break;
            case State::arith_q6:
                ungetChar(ch);
                return Token::ClosePar;
                break;
            // identifier
            case State::identifier_q0:
                if (((ch >= 'A') && (ch <= 'Z')) || (ch == '$') || ((ch >= 'a') && (ch <= 'z')) || (ch == '_')) {
                    text += ch;
                    state = State::identifier_q1;
                    ch = getNextChar();
                }
                else if (ch == EOF) {
                    text += ch;
                    return Token::Eof;
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::identifier_q1:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::identifier_q4;
                    ch = getNextChar();
                }
                else if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z')) || (ch == '_')) {
                    text += ch;
                    state = State::identifier_q2;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::identifier_q2:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::identifier_q2;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Ident;
                }
                break;
            case State::identifier_q4:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::identifier_q4;
                    ch = getNextChar();
                }
                else if (ch == '.') {
                    text += ch;
                    state = State::identifier_q5;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::identifier_q5:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::identifier_q5;
                    ch = getNextChar();
                }
                else if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::identifier_q2;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
        }
    }

}

const char *ExprLexer::tokenToString(Token tk)
{
    switch (tk) {
        case Token::ClosePar: return "ClosePar";
        case Token::OpenPar: return "OpenPar";
        case Token::Number: return "Number";
        case Token::OpSub: return "OpSub";
        case Token::Eof: return "Eof";
        case Token::OpAdd: return "OpAdd";
        case Token::Ident: return "Ident";
        case Token::OpMul: return "OpMul";
        case Token::OpDiv: return "OpDiv";
        default: return "Unknown";
    }
    
}
