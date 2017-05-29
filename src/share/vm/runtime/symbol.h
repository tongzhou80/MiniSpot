//
// Created by GentlyGuitar on 5/23/2017.
//

#ifndef MINISPOT_SYMBOL_H
#define MINISPOT_SYMBOL_H

#include <string>
#include <sstream>
#include "utilities/ostream.h"

class Symbol {
private:
    std::string _str;
public:
    Symbol();
    Symbol(const char*);
    Symbol& operator=(std::string s);
    Symbol& operator=(const char* s);
    std::string& str() { return _str; }
    const char* c_str() { return _str.c_str(); }
    std::vector<std::string> split(char delim) { return Strings::split(str(), delim); }
    Symbol& prepend(std::string);
    Symbol& append(std::string);
};

#endif //MINISPOT_SYMBOL_H
