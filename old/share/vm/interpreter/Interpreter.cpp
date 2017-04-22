//
// Created by GentlyGuitar on 12/11/2016.
//

#include <cstring>
#include "MethodFrame.h"
#include "Interpreter.h"
#include "Bytecode.h"
#include "../oops/JClass.h"
#include "../memory/Perm.h"
#include "../memory/Heap.h"


std::map<Bytecode::InsType , BytecodeRoutine> ThreadedInterpreter::routinedict;

void ThreadedInterpreter::initRoutineDict() {
    routinedict[Bytecode::BC_new] = ThreadedInterpreter::do_new;
}


void ThreadedInterpreter::do_new(Bytecode* bc, MethodFrame *frame) {
    printf("do new...\n");

    u1 index1 = bc->get_args_byte_(0);
    u1 index2 = bc->get_args_byte_(1);
    u2 windex1 = (u2)index1;
    u2 index = windex1 << 8 | index2;
    std::cout << frame->cp()->getClassname(index) << std::endl;
    JClass* klass = Perm::getClass(frame->cp()->getClassname(index));
    JObject* objectref = Heap::createJObject(klass);
}
