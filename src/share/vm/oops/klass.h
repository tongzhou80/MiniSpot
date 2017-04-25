//
// Created by tzhou on 4/24/17.
//

#ifndef MINISPOT_KLASS_H
#define MINISPOT_KLASS_H

//
// A Klass provides:
//  1: language level class object (method dictionary etc.)
//  2: provide vm dispatch behavior for the object
// Both functions are combined into one C++ class.

// One reason for the oop/klass dichotomy in the implementation is
// that we don't want a C++ vtbl pointer in every object.  Thus,
// normal oops don't have any virtual functions.  Instead, they
// forward all "virtual" functions to their klass, which does have
// a vtbl and does the C++ dispatch depending on the object's
// actual type.  (See oop.inline.hpp for some of the forwarding code.)
// ALL FUNCTIONS IMPLEMENTING THIS DISPATCH ARE PREFIXED WITH "oop_"!


#include "oop.h"
#include "../prims/jni.h"

class Klass {
    // note: put frequently-used fields together at start of klass structure
    // for better cache behavior (may not make much of a difference but sure won't hurt)
    enum { _primary_super_limit = 8 };

    // The "layout helper" is a combined descriptor of object layout.
    // For klasses which are neither instance nor array, the value is zero.
    //
    // For instances, layout helper is a positive number, the instance size.
    // This size is already passed through align_object_size and scaled to bytes.
    // The low order bit is set if instances of this class cannot be
    // allocated using the fastpath.
    //
    // For arrays, layout helper is a negative number, containing four
    // distinct bytes, as follows:
    //    MSB:[tag, hsz, ebt, log2(esz)]:LSB
    // where:
    //    tag is 0x80 if the elements are oops, 0xC0 if non-oops
    //    hsz is array header size in bytes (i.e., offset of first element)
    //    ebt is the BasicType of the elements
    //    esz is the element size in bytes
    // This packed word is arranged so as to be quickly unpacked by the
    // various fast paths that use the various subfields.
    //
    // The esz bits can be used directly by a SLL instruction, without masking.
    //
    // Note that the array-kind tag looks like 0x00 for instance klasses,
    // since their length in bytes is always less than 24Mb.
    //
    // Final note:  This comes first, immediately after C++ vtable,
    // because it is frequently queried.

    jint        _layout_helper;

    // The fields _super_check_offset, _secondary_super_cache, _secondary_supers
    // and _primary_supers all help make fast subtype checks.  See big discussion
    // in doc/server_compiler/checktype.txt
    //
    // Where to look to observe a supertype (it is &_secondary_super_cache for
    // secondary supers, else is &_primary_supers[depth()].
    juint       _super_check_offset;

    // Class name.  Instance classes: java/lang/String, etc.  Array classes: [I,
    // [Ljava/lang/String;, etc.  Set to zero for all other kinds of classes.
    //Symbol*     _name;

    // Cache of last observed secondary supertype
    Klass*      _secondary_super_cache;
    // Array of all secondary supertypes
    //Array<Klass*>* _secondary_supers;
    // Ordered list of all primary supertypes
    Klass*      _primary_supers[_primary_super_limit];
    // java/lang/Class instance mirroring this class
    oop       _java_mirror;
    // Superclass
    Klass*      _super;
    // First subclass (NULL if none); _subklass->next_sibling() is next one
    Klass*      _subklass;
    // Sibling link (or NULL); links all subklasses of a klass
    Klass*      _next_sibling;

    // All klasses loaded by a class loader are chained through these links
    Klass*      _next_link;

    // The VM's representation of the ClassLoader used to load this class.
    // Provide access the corresponding instance java.lang.ClassLoader.
    //ClassLoaderData* _class_loader_data;

    jint        _modifier_flags;  // Processed access flags, for use by Class.getModifiers.
    //AccessFlags _access_flags;    // Access flags. The class/interface distinction is stored here.


};



#endif //MINISPOT_KLASS_H
