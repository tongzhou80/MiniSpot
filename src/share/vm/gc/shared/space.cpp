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
    _size = 0;
    _full = NULL;
}

Space::Space(HeapWord *start, int word_size) {
    _bottom = start;
    _size = word_size;
    _end = _bottom + _size;
    _top = NULL;
    _full = false;
}

void Space::print(int level) {

}


ContiguousSpace::ContiguousSpace(HeapWord *start, int word_size) : Space(start, word_size) {

}

/* This function changes top() of the heap, so a Heap_lock is needed */
HeapWord* ContiguousSpace::allocate(int size) {
    HeapWord* result = NULL;
    {
        MutexLocker ml(Locks::Heap_lock);
        if (left() >= size) {
            result = top();
            set_top(top()+size);
        }
    }
    return result;
}