//
// Created by tzhou on 4/23/17.
//

#include <utilities/debug.h>
#include "universe.h"
#include "../runtime/globals.h"
#include "gc/shared/genCollectedHeap.h"

CollectedHeap* Universe::_collectedHeap = NULL;


jint Universe::init() {
    initialize_heap();
}

jint Universe::initialize_heap() {
    create_heap();
}

jint Universe::create_heap() {
    guarantee(_collectedHeap == NULL, "heap already created");
    if (UseSerialGC) {
        _collectedHeap = new GenCollectedHeap();
    }
    _collectedHeap->initialize();
}
