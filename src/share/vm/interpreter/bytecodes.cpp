//
// Created by GentlyGuitar on 11/15/2016.
//

#include "bytecodes.h"


Bytecode::Bytecode(JBCMeta *meta) {
    _type = meta->type;
    _name = meta->name;
    _arg_len = meta->arg_len;
}

Bytecode::~Bytecode() {
    delete _args;
}

