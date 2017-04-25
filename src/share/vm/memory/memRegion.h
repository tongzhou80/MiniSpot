//
// Created by tzhou on 4/24/17.
//

#ifndef MINISPOT_MEMREGION_H
#define MINISPOT_MEMREGION_H

// A very simple data structure representing a contigous region
// region of address space.

// Note that MemRegions are passed by value, not by reference.
// The intent is that they remain very small and contain no
// objects. _ValueObj should never be allocated in heap but we do
// create MemRegions (in CardTableModRefBS) in heap so operator
// new and operator new [] added for this special case.

#include <cstddef>
#include "../utilities/globalDefinitions.h"
#include "../utilities/debug.h"

class MemRegion {
    friend class VMStructs;
private:
    HeapWord* _start;
    size_t    _word_size;

public:
    MemRegion() : _start(NULL), _word_size(0) {};
    MemRegion(HeapWord* start, size_t word_size) :
            _start(start), _word_size(word_size) {};
    MemRegion(HeapWord* start, HeapWord* end) :
            _start(start), _word_size(pointer_delta(end, start)) {
        assert(end >= start, "incorrect constructor arguments");
    }
    MemRegion(MetaWord* start, MetaWord* end) :
            _start((HeapWord*)start), _word_size(pointer_delta(end, start)) {
        assert(end >= start, "incorrect constructor arguments");
    }

    MemRegion(const MemRegion& mr): _start(mr._start), _word_size(mr._word_size) {}

    HeapWord* start() const { return _start; }
    HeapWord* end() const   { return _start + _word_size; }
    HeapWord* last() const  { return _start + _word_size - 1; }

    void set_start(HeapWord* start) { _start = start; }
    void set_end(HeapWord* end)     { _word_size = pointer_delta(end, _start); }
    void set_word_size(size_t word_size) {
        _word_size = word_size;
    }

    bool contains(const MemRegion mr2) const {
        return _start <= mr2._start && end() >= mr2.end();
    }
    bool contains(const void* addr) const {
        return addr >= (void*)_start && addr < (void*)end();
    }
    bool equals(const MemRegion mr2) const {
        // first disjunct since we do not have a canonical empty set
        return ((is_empty() && mr2.is_empty()) ||
                (start() == mr2.start() && end() == mr2.end()));
    }

    size_t byte_size() const { return _word_size * sizeof(HeapWord); }
    size_t word_size() const { return _word_size; }

    bool is_empty() const { return word_size() == 0; }


};

#endif //MINISPOT_MEMREGION_H
