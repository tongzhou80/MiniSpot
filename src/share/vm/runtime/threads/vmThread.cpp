//
// Created by tzhou on 4/23/17.
//

#include "vmThread.h"
#include "../../utilities/debug.h"

VMThread* VMThread::_vm_thread = NULL;

VMThread::VMThread(): NamedThread() { /* parent constructor with no parameter should be automatically called */
    set_name((char*)"VM Thread");
}

void VMThread::create() {
    assert(vm_thread() == NULL, "we can only allocate one VMThread");
    _vm_thread = new VMThread();
}