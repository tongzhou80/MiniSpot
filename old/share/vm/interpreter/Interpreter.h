//
// Created by GentlyGuitar on 12/11/2016.
//

#ifndef MAGNOLIA_INTERPRETER_H
#define MAGNOLIA_INTERPRETER_H

#include "../global/TypeDef.h"
#include <map>

class Bytecode;
class MethodFrame;

typedef void (*BytecodeRoutine) (Bytecode* bc, MethodFrame* frame);

class ThreadedInterpreter {

public:
    static std::map<Bytecode::InsType, BytecodeRoutine> routinedict;
    static void initRoutineDict();

    static void do_aload_0(MethodFrame* frame);
    static void do_new(Bytecode* bc, MethodFrame* frame);
    static void do_dup(MethodFrame* frame);
    static void do_invokespecial(MethodFrame* frame);
};

#endif //MAGNOLIA_INTERPRETER_H
