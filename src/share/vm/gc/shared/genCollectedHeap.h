//
// Created by tzhou on 4/29/17.
//

#ifndef MINISPOT_GENCOLLECTEDHEAP_H
#define MINISPOT_GENCOLLECTEDHEAP_H

#include <prims/jni.h>

/* GenCollectedHeap is the heap used by serial and cms collector */

class CollectedHeap;
class Generation;

class GenCollectedHeap : public CollectedHeap {
private:
    Generation* _young_gen;
    Generation* _old_gen;
public:
    GenCollectedHeap();
    jint initialize();

    Generation* young_gen()  { return _young_gen; }
    Generation* old_gen()  { return _old_gen; }
};

#endif //MINISPOT_GENCOLLECTEDHEAP_H
