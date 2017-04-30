//
// Created by tzhou on 4/29/17.
//

#include <runtime/globals.h>
#include <stdlib.h>
#include "genCollectedHeap.h"
#include "collectedHeap.h"

/* for serial GC */
#include "gc/serial/defNewGeneration.h"
#include "gc/serial/tenuredGeneration.h"

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

    if (UseSerialGC) {
        _young_gen = new DefNewGeneration();
        _old_gen = new TenuredGeneration();
    }

    ZPPL("done init GenCollectedHeap");
}

size_t GenCollectedHeap::capacity() {
    //return _young_gen->capacity() + _old_gen->capacity();
}

HeapWord* GenCollectedHeap::mem_allocate(size_t size, bool *gc_overhead_limit_was_exceeded) {

}
