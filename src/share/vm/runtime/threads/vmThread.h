//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_VMTHREAD_H
#define MINISPOT_VMTHREAD_H

#include "namedThread.h"

//
// A single VMThread (the primordial thread) spawns all other threads
// and is itself used by other threads to offload heavy vm operations
// like scavenge, garbage_collect etc.
//

class VMThread: public NamedThread {
    // Pointer to single-instance of VM thread
    static VMThread* _vm_thread;

public:
    VMThread();


    /* static */
    static void create();
    static VMThread* vm_thread()  { return _vm_thread; }
};

#endif //MINISPOT_VMTHREAD_H
