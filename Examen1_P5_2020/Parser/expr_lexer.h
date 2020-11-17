#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "expr_symbols.h"

using SymbolInfo = std::pair<Symbol, std::string>;

class Lexer {
public:
    Lexer(const std::vector<SymbolInfo>& tklst): tklist(tklst) {
        it = tklist.begin();
    }

    Symbol getNextToken() {
        if (it == tklist.end()) {
            return Symbol::Eof;
        }
        Symbol tk = it->first;
        text = it->second;
        it++;
        
        return tk;
    }
    
    bool hasTokens() { return it != tklist.end(); }
    std::string getText() { return text; }

private:
    std::string text;
    std::vector<SymbolInfo> tklist;
    std::vector<SymbolInfo>::iterator it;
};
#endif
