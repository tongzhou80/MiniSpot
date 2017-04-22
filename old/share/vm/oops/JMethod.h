//
// Created by GentlyGuitar on 11/12/2016.
//

#ifndef MAGNOLIA_JMETHOD_H
#define MAGNOLIA_JMETHOD_H

#include <vector>
#include "../global/TypeDef.h"
#include "../classloader/ClassFile.h"
#include "../interpreter/Bytecode.h"

class JClass;
class MethodFrame;

class JMethod {
private:
    bool _acc_public;
    bool _acc_private;
    bool _acc_protected;
    bool _acc_static;
    bool _acc_final;
    bool _acc_synchronized;
    bool _acc_bridge;
    bool _acc_varargs;
    bool _acc_native;
    bool _acc_abstract;
    bool _acc_strict;
    bool _acc_synthetic;

    std::string _name;
    std::string _signature; // namely description in raw class file
    std::string _innername; // not include the class part, used for method looking up inside a class
    std::string _fullname;

    ClassFileMethodInfo* _rawmethod;
    JClass* _klass;
    ConstantPool* _cp;

    bool _code_parsed;
    ClassFileCodeAttribute* _code_attr;
    u1* _rawcode;
    int _parsebci;
    int _max_stack_depth;
    int _max_locals;
    int _code_length;
    std::vector<Bytecode*> _bytecodes_;


    u2 attributes_count;


    /* predefined attributes */


public:
    JMethod(ClassFileMethodInfo* rawmethod);
    JMethod(ClassFileMethodInfo* rawmethod, JClass*);
    ~JMethod();
    void init();
    void initMeta();
    void initCodeMeta();
    void parseCode();
    void threadedInterpret(MethodFrame*);

    ConstantPool* constantPool() { return _cp; }
    bool isCodeParsed() { return _code_parsed; }
    bool isReady();
    void cookMethod();

    std::string name() { return _name; }
    std::string innername() { return _innername; }
    std::string signature() { return _signature; }
    int max_stack() { return _max_stack_depth; }
    int max_locals() { return _max_locals; }
    int code_length() { return _code_length; }
    u1* rawcode() { return _rawcode; }
    int parsebci() { return _parsebci; }
    std::vector<Bytecode*> bytecodes() { return _bytecodes_; }



    bool is_acc_public() const {
        return _acc_public;
    }

    void set_acc_public(bool _acc_public) {
        JMethod::_acc_public = _acc_public;
    }

    bool is_acc_private() const {
        return _acc_private;
    }

    void set_acc_private(bool _acc_private) {
        JMethod::_acc_private = _acc_private;
    }

    bool is_acc_protected() const {
        return _acc_protected;
    }

    void set_acc_protected(bool _acc_protected) {
        JMethod::_acc_protected = _acc_protected;
    }

    bool is_acc_static() const {
        return _acc_static;
    }

    void set_acc_static(bool _acc_static) {
        JMethod::_acc_static = _acc_static;
    }

    bool is_acc_final() const {
        return _acc_final;
    }

    void set_acc_final(bool _acc_final) {
        JMethod::_acc_final = _acc_final;
    }

    bool is_acc_synchronized() const {
        return _acc_synchronized;
    }

    void set_acc_synchronized(bool _acc_synchronized) {
        JMethod::_acc_synchronized = _acc_synchronized;
    }

    bool is_acc_bridge() const {
        return _acc_bridge;
    }

    void set_acc_bridge(bool _acc_bridge) {
        JMethod::_acc_bridge = _acc_bridge;
    }

    bool is_acc_varargs() const {
        return _acc_varargs;
    }

    void set_acc_varargs(bool _acc_varargs) {
        JMethod::_acc_varargs = _acc_varargs;
    }

    bool is_acc_native() const {
        return _acc_native;
    }

    void set_acc_native(bool _acc_native) {
        JMethod::_acc_native = _acc_native;
    }

    bool is_acc_abstract() const {
        return _acc_abstract;
    }

    void set_acc_abstract(bool _acc_abstract) {
        JMethod::_acc_abstract = _acc_abstract;
    }

    bool is_acc_strict() const {
        return _acc_strict;
    }

    void set_acc_strict(bool _acc_strict) {
        JMethod::_acc_strict = _acc_strict;
    }

    bool is_acc_synthetic() const {
        return _acc_synthetic;
    }

    void set_acc_synthetic(bool _acc_synthetic) {
        JMethod::_acc_synthetic = _acc_synthetic;
    }
};



#endif //MAGNOLIA_JMETHOD_H
