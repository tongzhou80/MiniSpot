//
// Created by GentlyGuitar on 11/15/2016.
//

#include "Bytecode.h"
#include "MethodFrame.h"

Bytecode::Bytecode(JBCMeta *meta) {
    _type = meta->type_;
    _name = meta->name;
    _arg_len = meta->arg_len;
}

Bytecode::~Bytecode() {
    delete _args_;
}