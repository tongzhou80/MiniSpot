//
// Created by tzhou on 4/23/17.
//

#include <memory/universe.h>
#include "collectedHeap.h"


CollectedHeap::CollectedHeap() {
    _alignment = sizeof(HeapWord*);

}

void CollectedHeap::initialize_reserved_region(HeapWord *start, HeapWord *end) {
    // It is important to do this in a way such that concurrent readers can't                                                                                                                                          // temporarily think something is in the heap.  (Seen this happen in asserts.)                                                                                                                                     _reserved.set_word_size(0);
    _reserved.set_start(start);
    _reserved.set_end(end);
}

oop CollectedHeap::obj_allocate(KlassHandle klass, int size, TRAPS) {
    HeapWord* result = common_mem_allocate_init(klass, size, THREAD);
    return (oop)result;
}

HeapWord* CollectedHeap::common_mem_allocate_init(KlassHandle klass, size_t size, TRAPS) {
    HeapWord* result = common_mem_allocate_noinit(klass, size, THREAD);
    init_obj(result, size);
    return result;
}

void CollectedHeap::init_obj(HeapWord *obj, size_t size) {

}

HeapWord* CollectedHeap::common_mem_allocate_noinit(KlassHandle klass, size_t size, Thread *__the_thread__) {
    HeapWord* result = allocate_from_tlab(klass, THREAD, size);
    if (result) {
        return result;
    }

    bool gc_overhead_limit_was_exceeded = false;
    result = Universe::heap()->mem_allocate(size,
                                            &gc_overhead_limit_was_exceeded);


}

HeapWord* CollectedHeap::allocate_from_tlab(KlassHandle klass, Thread *thread, size_t size) {

}

HeapWord* CollectedHeap::allocate_from_tlab_slow(KlassHandle klass, Thread *thread, size_t size) {

}

