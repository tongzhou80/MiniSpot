//
// Created by tzhou on 4/24/17.
//

#ifndef MINISPOT_HANDLES_H
#define MINISPOT_HANDLES_H


#include "../utilities/debug.h"

class Klass;
class Thread;

class KlassHandle {
    Klass* _value;
protected:
    Klass* obj() const          { return _value; }
    Klass* non_null_obj() const { assert(_value != NULL, "resolving NULL _value"); return _value; }

public:
    KlassHandle()                                 : _value(NULL) {}
    KlassHandle(const Klass* obj)                 : _value(const_cast<Klass *>(obj)) {};
    KlassHandle(Thread* thread, const Klass* obj) : _value(const_cast<Klass *>(obj)) {};

    Klass* operator () () const { return obj(); }
    Klass* operator -> () const { return non_null_obj(); }

    bool operator == (Klass* o) const             { return obj() == o; }
    bool operator == (const KlassHandle& h) const { return obj() == h.obj(); }

    bool is_null() const  { return _value == NULL; }
    bool not_null() const { return _value != NULL; }
};

//
//class instanceKlassHandle : public KlassHandle {
//public:
//    /* Constructors */
//    instanceKlassHandle () : KlassHandle() {}
//    instanceKlassHandle (const Klass* k) : KlassHandle(k) {
//        assert(k == NULL || is_instanceKlass(k), "illegal type");
//    }
//    instanceKlassHandle (Thread* thread, const Klass* k) : KlassHandle(thread, k) {
//        assert(k == NULL || is_instanceKlass(k), "illegal type");
//    }
//    /* Access to klass part */
//    InstanceKlass*       operator () () const { return (InstanceKlass*)obj(); }
//    InstanceKlass*       operator -> () const { return (InstanceKlass*)obj(); }
//
//};


#endif //MINISPOT_HANDLES_H
