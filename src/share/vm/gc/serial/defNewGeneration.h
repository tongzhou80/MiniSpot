//
// Created by tzhou on 4/29/17.
//

#ifndef MINISPOT_DEFNEWGENERATION_H
#define MINISPOT_DEFNEWGENERATION_H


#include <gc/shared/generation.h>
#include <gc/shared/space.h>

class DefNewGeneration : public Generation {
protected:
    ContiguousSpace* _eden_space;
    ContiguousSpace* _from_space;
    ContiguousSpace* _to_space;
public:
    ContiguousSpace* eden_space() { return _eden_space; }
    ContiguousSpace* from_space() { return _from_space;}
    ContiguousSpace* to_space()   { return  _to_space; }

    bool collect();
    HeapWord* allocate(int word_size);
};

#endif //MINISPOT_DEFNEWGENERATION_H
