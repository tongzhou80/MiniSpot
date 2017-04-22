//
// Created by GentlyGuitar on 12/12/2016.
//

#include <cstring>
#include "MethodFrame.h"
#include "ExecThread.h"
#include "../oops/JMethod.h"
#include "../util/SysUtil.h"
#include "Interpreter.h"


MethodFrame::MethodFrame(JMethod* m) {
    _method = m;
    _max_stack_depth = m->max_stack();
    _max_locals = m->max_locals();
    _code_len = m->code_length();
    _cp = m->constantPool();
}

