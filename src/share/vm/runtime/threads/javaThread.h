//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_JAVATHREAD_H
#define MINISPOT_JAVATHREAD_H


#include <runtime/handles.h>
#include "../../prims/jni.h"
#include "thread.h"

class Thread;

class JavaThread: public Thread {
public:
// JavaThreadState keeps track of which part of the code a thread is executing in. This
// information is needed by the safepoint code.
//
// There are 4 essential states:
//
//  _thread_new         : Just started, but not executed init. code yet (most likely still in OS init code)
//  _thread_in_native   : In native code. This is a safepoint region, since all oops will be in jobject handles
//  _thread_in_vm       : Executing in the vm
//  _thread_in_Java     : Executing either interpreted or compiled Java code (or could be in a stub)
//
// Each state has an associated xxxx_trans state, which is an intermediate state used when a thread is in
// a transition from one state to another. These extra states makes it possible for the safepoint code to
// handle certain thread_states without having to suspend the thread - making the safepoint code faster.
//
// Given a state, the xxx_trans state can always be found by adding 1.
//
    enum JavaThreadState {
        _thread_uninitialized     =  0, // should never happen (missing initialization)
        _thread_new               =  2, // just starting up, i.e., in process of being initialized
        _thread_new_trans         =  3, // corresponding transition state (not used, included for completness)
        _thread_in_native         =  4, // running in native code
        _thread_in_native_trans   =  5, // corresponding transition state
        _thread_in_vm             =  6, // running in VM
        _thread_in_vm_trans       =  7, // corresponding transition state
        _thread_in_Java           =  8, // running in Java or in stub code
        _thread_in_Java_trans     =  9, // corresponding transition state (not used, included for completness)
        _thread_blocked           = 10, // blocked in vm
        _thread_blocked_trans     = 11, // corresponding transition state
        _thread_max_state         = 12  // maximum thread state+1 - used for statistics allocation
    };

    //friend class VMStructs;
private:
    JavaThread *_next;                          // The next thread in the Threads list
    //oop            _threadObj;                     // The Java level thread object
    JavaThreadState _thread_state;
    JNIEnv        _jni_environment;
    bool _jni_attach_state;

    InstanceKlass* _caller_class;
public:
    JavaThread(bool is_attaching_via_jni=false);
    void initialize();

    enum JNIAttachStates {
        _not_attaching_via_jni = 1,  // thread is not attaching via JNI
        _attaching_via_jni,          // thread is attaching via JNI
        _attached_via_jni            // thread has attached via JNI
    };
    void set_next(JavaThread* next)  { _next = next;}
    JavaThreadState thread_state() const           { return _thread_state; }
    void set_thread_state(JavaThreadState s)       { _thread_state = s;    }

    bool has_pending_exception();

    JNIEnv* jni_environment()                      { return &_jni_environment; }
    InstanceKlass* caller_class()                  { return _caller_class; }

    /* Static */
    // Returns the running thread as a JavaThread
    static JavaThread* current();
};


#endif //MINISPOT_JAVATHREAD_H
