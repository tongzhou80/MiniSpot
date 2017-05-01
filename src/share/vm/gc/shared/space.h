//
// Created by tzhou on 4/30/17.
//

#ifndef MINISPOT_SPACE_H
#define MINISPOT_SPACE_H

#include <utilities/globalDefinitions.h>

// Supports allocation, space operation and GC
class Space {
protected:
    HeapWord* _bottom;
    HeapWord* _top;
    HeapWord* _end;
    int _size;
    bool _full;
public:
    Space();
    Space(HeapWord* start, int word_size);
    ~Space() { /* not care for now */ };

    virtual void print(int level);

    // Accessors                                                                                                                                                                                                       HeapWord* top() const                    { return _top;    }
    virtual void set_top(HeapWord* value)    { _top = value;   }
    HeapWord* top()                          { return _top; }
    HeapWord* bottom() const                 { return _bottom; }
    virtual void set_bottom(HeapWord* value) { _bottom = value; }
    HeapWord* end() const                    { return _end; }
    virtual void set_end(HeapWord* value)    { _end = value; }
    int size_in_words()                      { return _size; }
    int size_in_Ms()                         { return WtoM(_size); }

    HeapWord** top_addr()                    { return &_top; }
    HeapWord** end_addr()                    { return &_end; }
    int used_in_words()                      { return ::pointer_delta(top(), bottom(), sizeof(HeapWord*)); }
    int used_in_MB()                         { return WtoM(used_in_words()); }
    int left()                               { return ::pointer_delta(end(), top(), sizeof(HeapWord*)); }
    bool contains(const void* p) const       { return _bottom <= p && p < _end; }
    bool full()                              { return _full; }
    void set_full(bool is_full)              { _full = is_full; }

};

class ContiguousSpace : public Space {
public:
    ContiguousSpace(HeapWord* start, int word_size);
    HeapWord* allocate(int size);
};

#endif //MINISPOT_SPACE_H
