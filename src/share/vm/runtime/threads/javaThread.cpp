//
// Created by tzhou on 4/23/17.
//

#include "javaThread.h"
#include "prims/jni.h"

JavaThread::JavaThread(bool is_attaching_via_jni) : Thread() {
    initialize();
    if (is_attaching_via_jni) {
        _jni_attach_state = _attaching_via_jni;
    } else {
        _jni_attach_state = _not_attaching_via_jni;
    }
}

void JavaThread::initialize() {
    _next = NULL;
    _jni_environment.functions = jni_functions();
    _thread_state = _thread_new;
    _jni_attach_state = _not_attaching_via_jni;
    _caller_class = NULL;

    Threads::add(this);
}


// Inline implementation of JavaThread::current
JavaThread* JavaThread::current() {
    return (JavaThread*)Thread::current();
}
