//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_UNIVERSE_H
#define MINISPOT_UNIVERSE_H

#include "../prims/jni.h"

class CollectedHeap;

class Universe {


public:
    /* static */
    static CollectedHeap* _collectedHeap;

    static jint init();
    static jint initialize_heap();
    static jint create_heap();
    static CollectedHeap* heap() { return _collectedHeap; }
};

#endif //MINISPOT_UNIVERSE_H
