//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_THREAD_H
#define MINISPOT_THREAD_H

#include <iostream>
#include <map>
#include "../utilities/debug.h"
#include "../prims/jni.h"
#include "osThread.h"

// Class hierarchy
// - Thread
//   - NamedThread
//     - VMThread
//     - ConcurrentGCThread
//     - WorkerThread
//       - GangWorker
//       - GCTaskThread
//   - JavaThread
//   - WatcherThread

class Threads;

class Thread {
public:
    OSThread* _osthread;

public:
    // Constructor
    Thread();
    virtual ~Thread();

    // initializtion
    void initialize_thread_local_storage();

    // thread entry point
    virtual void run();

    // OSThread
    OSThread* osthread()  { return _osthread; }
    void set_osthread(OSThread* osThread)  { _osthread = osThread; }

    // Testers
    virtual bool is_VM_thread()       const            { return false; }
    virtual bool is_Java_thread()     const            { return false; }
    virtual bool is_Compiler_thread() const            { return false; }
    virtual bool is_Code_cache_sweeper_thread() const  { return false; }
    virtual bool is_hidden_from_external_view() const  { return false; }
    virtual bool is_jvmti_agent_thread() const         { return false; }
    // True iff the thread can perform GC operations at a safepoint.
    // Generally will be true only of VM thread and parallel GC WorkGang
    // threads.
    virtual bool is_GC_task_thread() const             { return false; }
    virtual bool is_Watcher_thread() const             { return false; }
    virtual bool is_Sampler_thread() const             { return false; }
    virtual bool is_ConcurrentGC_thread() const        { return false; }
    virtual bool is_Named_thread() const               { return false; }
    virtual bool is_Worker_thread() const              { return false; }

    virtual char* name() const { return (char*)"Unknown thread"; }

    static Thread* current();

};

class Threads {
#ifdef __linux__
private:
    static std::map<pthread_t, Thread*> _threads_table;
public:
    static Thread* get_pthread_by_id(pthread_t id)  { return _threads_table[id]; }
    static void register_thread(Thread*);
#endif
public:
    static jint create_vm(JavaVMInitArgs* args, bool* canTryAgain);
    static bool destroy_vm();
};



#ifdef __linux__

inline Thread* Thread::current() {
#ifdef ASSERT
    // This function is very high traffic. Define PARANOID to enable expensive
    // asserts.

#endif
    Thread* thread = Threads::get_pthread_by_id(pthread_self());
    assert(thread != NULL, "just checking");
    return thread;
}


#endif
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

class JavaThread: public Thread {
    //friend class VMStructs;
private:
    JavaThread *_next;                          // The next thread in the Threads list
    //oop            _threadObj;                     // The Java level thread object
    JavaThreadState _thread_state;
    JNIEnv        _jni_environment;
public:
    JavaThreadState thread_state() const           { return _thread_state; }
    void set_thread_state(JavaThreadState s)       { _thread_state = s;    }

    bool has_pending_exception();

    JNIEnv* jni_environment()                      { return &_jni_environment; }

    /* Static */
    // Returns the running thread as a JavaThread
    static inline JavaThread* current();
};



// Inline implementation of JavaThread::current
inline JavaThread* JavaThread::current() {
    return (JavaThread*)Thread::current();
}



#endif //MINISPOT_THREAD_H
