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

Symbol& Symbol::prepend(std::string pre) {
    _str = pre + _str;
    return *this;
}

Symbol& Symbol::append(std::string ap) {
    _str += ap;
    return *this;
}
