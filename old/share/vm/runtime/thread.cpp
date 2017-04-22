//
// Created by tzhou on 4/20/17.
//

#include "thread.h"

jint Threads::create_vm(JavaVMInitArgs* args, bool* canTryAgain) {
    VMThread::create();
    Thread* vmthread = VMThread::vm_thread();
    if (!os::create_thread(vmthread, os::vm_thread)) {

    }
    os::start_thread(vmthread);
}
