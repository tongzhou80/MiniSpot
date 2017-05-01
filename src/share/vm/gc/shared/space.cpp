//
// Created by tzhou on 4/30/17.
//

#include <utilities/debug.h>
#include <runtime/atomic.h>
#include <runtime/mutex.h>
#include "space.h"

Space::Space() {
    _bottom = NULL;
    _top = NULL;
    _bottom = NULL;
    _size = NULL;
    _full = NULL;
}

Space::Space(HeapWord *start, int word_size) {
    _bottom = start;
    _size = word_size;
    _end = _bottom + _size;
    _top = NULL;
    _full = false;
}


ContiguousSpace::ContiguousSpace(HeapWord *start, int word_size) : Space(start, word_size) {

}

HeapWord* ContiguousSpace::cas_allocate(int size) {
    {
        MutexLocker ml;
    }


    HeapWord* last_top = top();
    do {
        HeapWord* obj = top();
        if (::pointer_delta(end(), obj, sizeof(HeapWord*)) >= size) {
            HeapWord* new_top = obj + size;
            HeapWord* result = (HeapWord*)Atomic::cmpxchg_ptr(new_top, top_addr(), obj);
            // result can be one of two:
            //  the old top value: the exchange succeeded                                                                                                                                                                      //  otherwise: the new value of the top is returned.                                                                                                                                                               if (result != obj) {
            continue; // another thread beat us to the allocation, try again                                                                                                                                                 }
            assert(is_object_aligned((intptr_t)obj) && is_object_aligned((intptr_t)new_top),
                   "checking alignment");

            return obj;
        } else {
            _full = true;
            return NULL;
        }
    } while (true);
}