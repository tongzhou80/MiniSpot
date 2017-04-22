//
// Created by GentlyGuitar on 11/12/2016.
//

#include <cstring>
#include "JMethod.h"
#include "JClass.h"
#include "../util/SysUtil.h"
#include "../interpreter/MethodFrame.h"
#include "../interpreter/Interpreter.h"
#include "../interpreter/Bytecode.h"


JMethod::JMethod(ClassFileMethodInfo *rawmethod, JClass* jc) {
    _rawmethod = rawmethod;
    _code_attr = rawmethod->code;
    _rawcode = _code_attr->code;
    _klass = jc;
    _cp = jc->constantPool();
    _code_parsed = false;

    _acc_public = rawmethod->acc_public;
    _acc_private = rawmethod->acc_private;
    _acc_protected = rawmethod->acc_protected;
    _acc_static = rawmethod->acc_static;



    init();
}

JMethod::JMethod(ClassFileMethodInfo* raw) {
    _rawmethod = raw;
    init();
}

JMethod::~JMethod() {
    if (_code_parsed) {
        for (int i = 0; i < _bytecodes_.size(); i++) {
            delete _bytecodes_[i];
        }
    }
}

void JMethod::init() {
    initMeta();
    initCodeMeta();
}

void JMethod::initMeta() {
    _cp = _klass->constantPool();
    _name = (char*)((ConstantUtf8Info*)(_cp->get(_rawmethod->name_index, ConstantPool::ConstantUtf8)))->bytes;
    _signature = (char*)((ConstantUtf8Info*)(_cp->get(_rawmethod->descriptor_index, ConstantPool::ConstantUtf8)))->bytes;
    _innername = _name + _signature;
    _fullname = _klass->name() + _innername;

    /* check main method arg type and return type */
    if (_name == "main") {
        if (_signature != "([Ljava/lang/String;)V") {
            std::cerr << "Error: Main method must return a value of type void and accept String[] as argument, please\n"
                                 "define the main method as:\n"
                                 "   public static void main(String[] args)" << std::endl;
        }
    }

    if (ClassLoadingVerbose) {
        std::cout << "init method " << _name << std::endl;
        std::cout << "    meta..." << std::endl;
    }
}

void JMethod::initCodeMeta() {
    _max_stack_depth = _code_attr->max_stack;
    _max_locals = _code_attr->max_locals;
    _code_length = _code_attr->code_length;


}

/* Bytecode parsing is also a threaded fasion */
void JMethod::parseCode() {
    if (!isCodeParsed()) {
        _bytecodes_ = ClassParser::parseBytecode(_rawcode, _code_length);
        _code_parsed = true;
    }
}

bool JMethod::isReady() {
    bool ready = true;
    if (!isCodeParsed()) {
        ready = false;
    }
    return ready;
}

void JMethod::cookMethod() {
    parseCode();
}

//void JMethod::threadedInterpret(MethodFrame* frame) {
//    if (isCodeParsed()) {
//        std::cerr << "bytecode should not be parsed before threaded interpreting" << std::endl;
//        exit(0);
//    }
//
//    int p = 0;
//    while (p < _code_length) {
//        char opcode;
//        std::memcpy(&opcode, _code_attr->code+p, sizeof(char));
//        p += sizeof(char);
//        std::cout << SysUtil::bcdict[opcode];
//        BytecodeRoutine routine = ThreadedInterpreter::routinedict[opcode];
//        routine(frame);
//        break;
//    }
//}
