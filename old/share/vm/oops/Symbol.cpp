//
// Created by GentlyGuitar on 12/20/2016.
//

#include "Symbol.h"

LegitMethodName::LegitMethodName(std::string cl, std::string m, std::string sig) {
    _klass = cl;
    _method = m;
    _sig = sig;
    _value = _klass + '.' + _method + _sig;
}

std::string LegitMethodName::getClassPart() {
    return _klass;
}

std::string LegitMethodName::getMethodPart() {
    return _method + _sig;
}

std::string LegitMethodName::str() {
    return _value;
}

