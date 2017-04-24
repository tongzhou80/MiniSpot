//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_UNIVERSE_H
#define MINISPOT_UNIVERSE_H

#include "../prims/jni.h"

class Universe {


public:
    /* static */
    static jint universe_init();
    static jint initialize_heap();
    static jint create_heap();
};

#endif //MINISPOT_UNIVERSE_H
