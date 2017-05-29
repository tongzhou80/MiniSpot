//
// Created by GentlyGuitar on 4/21/2017.
//

#include "osThread.h"
#include "../mutex.h"

OSThread::OSThread() {
    intialize();
}

OSThread::OSThread(OSThreadStartFunc start_proc, void *start_parm) {
    _start_proc = start_proc;
    _start_parm = start_parm;
    intialize();
}

void OSThread::intialize() {
    _startThread_lock = new Monitor();
}
