//
// Created by tzhou on 4/29/17.
//

#ifndef MINISPOT_GENCOLLECTEDHEAP_H
#define MINISPOT_GENCOLLECTEDHEAP_H

#include <prims/jni.h>
#include <utilities/globalDefinitions.h>
#include "collectedHeap.h"

/* GenCollectedHeap is the heap used by serial and cms collector */

class Generation;

class GenCollectedHeap : public CollectedHeap {
private:
    Generation* _young_gen;
    Generation* _old_gen;
public:
    GenCollectedHeap();
    jint initialize();

    size_t capacity();
    bool is_in(void*);
    bool is_scavengable(void*);
    bool supports_tlab_allocation()  { return true; }
    size_t tlab_capacity(Thread*);
    size_t tlab_used(Thread*);

    Generation* young_gen()  { return _young_gen; }
    Generation* old_gen()  { return _old_gen; }

    void collect(GCCause::Cause);
    void do_full_collection(bool);

    HeapWord* mem_allocate(size_t size,
                           bool* gc_overhead_limit_was_exceeded);
};

#endif //MINISPOT_GENCOLLECTEDHEAP_H
