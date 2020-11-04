#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define _Print {Token::KwPrint, "Print" }
#define _Semicolon {Token::Semicolon, ";" }
#define _OpenPar {Token::OpenPar, "(" }
#define _ClosePar {Token::ClosePar, ")" }
#define _Comma {Token::Comma, "," }
#define _OpAssign {Token::OpAssign, "=" }
#define _OpAdd {Token::OpAdd, "+" }
#define _OpSub {Token::OpSub, "-" }
#define _OpMul {Token::OpMul, "*" }
#define _OpDiv {Token::OpDiv, "/" }
#define _Number(txt) {Token::Number, txt }
#define _Ident(txt) {Token::Ident, txt }
#define _Eof {Token::Eof, "<Eof>" }

enum class Token { 
    KwPrint,
    Semicolon,
    OpenPar, 
    ClosePar,
    Comma,
    OpAssign,
    OpAdd,
    OpSub,
    OpMul,
    OpDiv, 
    Number,
    Ident, 
    Unknown, 
    Eof
};

struct TokenInfo {
    Token token_id;
    std::string token_text;
};

class Lexer {
public:
	Lexer(const std::vector<TokenInfo>& tklst): tklist(tklst) {
        it = tklist.begin();
    }

    int getLineNo() { return 1; }

    Token getNextToken() {
        Token tk = it->token_id;
        text = it->token_text;
        
        if (it != tklist.end()) {
            it++;
        }
        
        return tk;
    }
    
    bool hasTokens() { return it != tklist.end(); }
    std::string getText() { return text; }

private:
    std::string text;
    std::vector<TokenInfo> tklist;
    std::vector<TokenInfo>::iterator it;
};
#endif
