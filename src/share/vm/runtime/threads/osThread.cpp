//
// Created by GentlyGuitar on 4/21/2017.
//

#include "osThread.h"
#include "../mutex.h"

OSThread::OSThread() {
    _startThread_lock = new Monitor();
}
