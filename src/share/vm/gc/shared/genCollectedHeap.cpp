//
// Created by tzhou on 4/29/17.
//

#include <runtime/globals.h>
#include <stdlib.h>
#include "genCollectedHeap.h"
#include "collectedHeap.h"

GenCollectedHeap::GenCollectedHeap() : CollectedHeap() {
    _size = MtoB(200);
    if (NewSizeInMB != 0) {
        _size = MtoW(NewSizeInMB);
    }

    if (NewSize != 0) {
        _size = BtoW(NewSize);
    }
}

jint GenCollectedHeap::initialize() {
    HeapWord* heap_address = (HeapWord*)aligned_alloc(_alignment, _size);
    guarantee(heap_address != NULL, "allocate space for heap failed");
    initialize_reserved_region(heap_address, heap_address+size());

}

