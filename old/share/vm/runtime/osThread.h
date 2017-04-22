//
// Created by tzhou on 4/21/17.
//

#ifndef MAGNOLIA_OSTHREAD_H
#define MAGNOLIA_OSTHREAD_H

// The OSThread class holds OS-specific thread information.  It is equivalent
// to the sys_thread_t structure of the classic JVM implementation.

// The thread states represented by the ThreadState values are platform-specific
// and are likely to be only approximate, because most OSes don't give you access
// to precise thread state information.

// Note: the ThreadState is legacy code and is not correctly implemented.
// Uses of ThreadState need to be replaced by the state in the JavaThread.

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


#endif //MAGNOLIA_OSTHREAD_H
