//
// Created by GentlyGuitar on 5/23/2017.
//

#include "symbol.h"

Symbol::Symbol() {

}

Symbol& Symbol::operator=(std::string s) {
    _str = s;
}

Symbol& Symbol::operator=(const char *s) {
    _str = s;
}

Symbol::Symbol(const char * name) {
    _str = name;
}

