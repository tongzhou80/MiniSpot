//
// Created by GentlyGuitar on 11/15/2016.
//

#ifndef MAGNOLIA_BYTECODE_H
#define MAGNOLIA_BYTECODE_H

#include "../global/TypeDef.h"
#include <map>
#include <cstring>
#include <cassert>

class Bytecode;
class JBCMeta;
class MethodFrame;

class Bytecode {
public:
    enum InsType {
        BC_iload,
        BC_aload,
        BC_iconst,
        BC_new,
        BC_dup,
        BC_invokespecial,
    };
private:
    InsType _type;
    std::string _name;
    int _line;
    u1* _args_;
    int _arg_len;
public:
    Bytecode(JBCMeta* meta);
    ~Bytecode();
    u1 get_args_byte_(int i) const {
        assert(i < _arg_len);
        return _args_[i];
    }

    void set_args_(u1 *src, int len) {
        _arg_len = len;
        this->_args_ = (u1*)new char[_arg_len];
        std::memcpy(this->_args_, src+1, _arg_len);
    }

    void set_args_(u1 *src) {
        this->_args_ = (u1*)new char[_arg_len];
        std::memcpy(this->_args_, src+1, _arg_len);
    }

    InsType get_type() const {
        return _type;
    }

    void set_type(InsType _type) {
        Bytecode::_type = _type;
    }

    int get_line() const {
        return _line;
    }

    void set_line(int _line) {
        Bytecode::_line = _line;
    }



};

struct JBCMeta {
public:
    Bytecode::InsType type_;
    std::string name;
    int arg_len;
    JBCMeta(Bytecode::InsType type_, std::string name, int len) : type_(type_), name(name), arg_len(len) { }
};



//
//class JBC_iload: public Bytecode {
//    int index;
//public:
//    JBC_iload(int index) { type = BC_iload; this->index = index; }
//    void exec(MethodFrame* & frame);
//};
//
//class JBC_iconst: public Bytecode {
//    int value;
//public:
//    JBC_iconst() { type = BC_iconst; this->value = value; }
//    void exec(MethodFrame* & frame);
//};

#endif //MAGNOLIA_INSTRUCTION_H
