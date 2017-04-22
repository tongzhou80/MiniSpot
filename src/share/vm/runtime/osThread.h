//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_OSTHREAD_H
#define MINISPOT_OSTHREAD_H

// The OSThread class holds OS-specific thread information.  It is equivalent
// to the sys_thread_t structure of the classic JVM implementation.

// The thread states represented by the ThreadState values are platform-specific
// and are likely to be only approximate, because most OSes don't give you access
// to precise thread state information.

// Note: the ThreadState is legacy code and is not correctly implemented.
// Uses of ThreadState need to be replaced by the state in the JavaThread.

#include "../prims/jni.h"
#include "../utilities/globalDefinitions.h"

enum ThreadState {
    ALLOCATED,                    // Memory has been allocated but not initialized
    INITIALIZED,                  // The thread has been initialized but yet started
    RUNNABLE,                     // Has been started and is runnable, but not necessarily running
    MONITOR_WAIT,                 // Waiting on a contended monitor lock
    CONDVAR_WAIT,                 // Waiting on a condition variable
    OBJECT_WAIT,                  // Waiting on an Object.wait() call
    BREAKPOINTED,                 // Suspended at breakpoint
    SLEEPING,                     // Thread.sleep()
    ZOMBIE                        // All done, but not reclaimed yet
};

class OSThread {
    friend class VMStructs;

private:
    OSThreadStartFunc _start_proc;  // Thread start routine
    void *_start_parm;              // Thread start routine parameter
    ThreadState _state;    // Thread state *hint*
    jint _interrupted;     // Thread.isInterrupted state
    //  volatile ThreadState _state;    // Thread state *hint*
    //  volatile jint _interrupted;     // Thread.isInterrupted state

    // Note:  _interrupted must be jint, so that Java intrinsics can access it.
    // The value stored there must be either 0 or 1.  It must be possible
    // for Java to emulate Thread.currentThread().isInterrupted() by performing
    // the double indirection Thread::current()->_osthread->_interrupted.

    // Methods
public:
    void set_state(ThreadState state) { _state = state; }

    ThreadState get_state() { return _state; }

    OSThread(OSThreadStartFunc start_proc, void *start_parm);

    ~OSThread();

    // Accessors
    OSThreadStartFunc start_proc() const { return _start_proc; }

    void set_start_proc(OSThreadStartFunc start_proc) { _start_proc = start_proc; }

    void *start_parm() const { return _start_parm; }

    void set_start_parm(void *start_parm) { _start_parm = start_parm; }

    volatile bool interrupted() const { return _interrupted != 0; }

    void set_interrupted(bool z) { _interrupted = z ? 1 : 0; }

    // Printing

    // Platform dependent stuff
};





#endif //MINISPOT_OSTHREAD_H
