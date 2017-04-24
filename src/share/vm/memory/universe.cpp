//
// Created by tzhou on 4/23/17.
//

#include "universe.h"
#include "../runtime/globals.h"

jint Universe::universe_init() {
    initialize_heap();
}

jint Universe::initialize_heap() {
    create_heap();
}

jint Universe::create_heap() {
    if (UseSerialGC) {

    }
}
