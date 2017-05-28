//
// Created by GentlyGuitar on 5/23/2017.
//

#ifndef MINISPOT_SYMBOL_H
#define MINISPOT_SYMBOL_H

#include <string>

class Symbol {
private:
    std::string _str;
public:
    Symbol();
    Symbol(const char*);
    Symbol& operator=(std::string s);
    Symbol& operator=(const char* s);
    std::string str() { return _str; }
};

#endif //MINISPOT_SYMBOL_H
