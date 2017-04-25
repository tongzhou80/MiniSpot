//
// Created by tzhou on 4/24/17.
//

#ifndef MINISPOT_OOP_H
#define MINISPOT_OOP_H


#include <cstdint>
#include "oopsHierarchy.h"


class markOopDesc;
class Klass;

class oopDesc {
    friend class VMStructs;

private:
    /* a markOop is actually also an oop whose value could be interpreted in a specific way instead of as an plain address */
    volatile markOop _mark;
    union _metadata {
        Klass *_klass;
        //narrowKlass _compressed_klass;
    } _metadata;

};


class markOopDesc: public oopDesc {
private:
    // Conversion
    uintptr_t value() const {
        return (uintptr_t)
        this;
    }
};
#endif //MINISPOT_OOP_H
