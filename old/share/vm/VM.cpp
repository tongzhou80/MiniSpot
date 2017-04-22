//
// Created by GentlyGuitar on 12/14/2016.
//

#include "VM.h"
#include "classloader/ClassLoader.h"
#include "interpreter/ExecThread.h"
#include "memory/JClassArea.h"
#include "memory/JMethodArea.h"
#include "util/SysUtil.h"
#include "interpreter/Interpreter.h"

VM::VM() {

}

void VM::initPerm() {
    //_classarea_ = new JClassArea();
}

void VM::parseArgs() {
    _classname = "Inc.class";
}

void VM::start() {
    /* not work */
//    std::thread exec(spawnExecThread);
//    exec.join();


    parseArgs();
    SysUtil::init_bcdict();
    ThreadedInterpreter::initRoutineDict();

    spawnExecThread();

}

void VM::spawnExecThread() {
    ExecThread* engine = new ExecThread(this);
    engine->start();

    delete engine;

}

VM::~VM() {
    //delete _classarea_;
}