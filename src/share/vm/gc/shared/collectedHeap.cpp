//
// Created by tzhou on 4/23/17.
//

#include "collectedHeap.h"

CollectedHeap::CollectedHeap() {
    _alignment = sizeof(HeapWord*);

}

void CollectedHeap::initialize_reserved_region(HeapWord *start, HeapWord *end) {
    // It is important to do this in a way such that concurrent readers can't                                                                                                                                          // temporarily think something is in the heap.  (Seen this happen in asserts.)                                                                                                                                     _reserved.set_word_size(0);
    _reserved.set_start(start);
    _reserved.set_end(end);
}


