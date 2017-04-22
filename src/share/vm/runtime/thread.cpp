//
// Created by GentlyGuitar on 4/21/2017.
//

#include "thread.h"


jint Threads::create_vm(JavaVMInitArgs *args, bool *canTryAgain) {
    // Attach the main thread to this os thread
    JavaThread* main_thread = new JavaThread();
    main_thread->set_thread_state(_thread_in_vm);
}