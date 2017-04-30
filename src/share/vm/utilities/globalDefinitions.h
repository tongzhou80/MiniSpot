//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_GLOBALDEFINITIONS_H
#define MINISPOT_GLOBALDEFINITIONS_H

#include <cstddef>
#include <cstdint>
#include "exceptions.h"

#define PID_FORMAT "%lld"

typedef int (*OSThreadStartFunc)(void*);

// An opaque struct of heap-word width, so that HeapWord* can be a generic
// pointer into the heap.  We require that object sizes be measured in
// units of heap words, so that that
//   HeapWord* hw;
//   hw += oop(hw)->foo();
// works, where foo is a method (like size or scavenge) that returns the
// object size.
class HeapWord {
    friend class VMStructs;
private:
    char* i;
#ifndef PRODUCT
public:
    char* value() { return i; }
#endif
};

// Analogous opaque struct for metadata allocated from
// metaspaces.
class MetaWord {
    friend class VMStructs;
private:
    char* i;
};


// Pointer subtraction.
// The idea here is to avoid ptrdiff_t, which is signed and so doesn't have
// the range we might need to find differences from one end of the heap
// to the other.
// A typical use might be:
//     if (pointer_delta(end(), top()) >= size) {
//       // enough room for an object of size
//       ...
// and then additions like
//       ... top() + size ...
// are safe because we know that top() is at least size below end().
inline size_t pointer_delta(const void* left,
                            const void* right,
                            size_t element_size) {
    return (((uintptr_t) left) - ((uintptr_t) right)) / element_size;
}
// A version specialized for HeapWord*'s.
inline size_t pointer_delta(const HeapWord* left, const HeapWord* right) {
    return pointer_delta(left, right, sizeof(HeapWord));
}
// A version specialized for MetaWord*'s.
inline size_t pointer_delta(const MetaWord* left, const MetaWord* right) {
    return pointer_delta(left, right, sizeof(MetaWord));
}


// Size convert
inline int BtoW(int Bs) {
    return Bs/sizeof(HeapWord*);
}

inline int BtoK(int Bs) {
    return Bs/1024;
}

inline int BtoM(int Bs) {
    return Bs/1024/1024;
}

inline int WtoB(int Ws) {
    return Ws*sizeof(HeapWord*);
}

inline int WtoK(int Ws) {
    return WtoB(Ws)/1024;
}

inline int WtoM(int Ws) {
    return WtoB(Ws)/1024/1024;
}

inline int MtoB(int Ms) {
    return Ms*1024*1024;
}

inline int MtoW(int Ms) {
    return BtoW(MtoB(Ms));
}


#endif //MINISPOT_GLOBALDEFINITIONS_H
