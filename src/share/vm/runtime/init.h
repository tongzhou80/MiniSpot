//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_INIT_H
#define MINISPOT_INIT_H

// init_globals replaces C++ global objects so we can use the standard linker
// to link Delta (which is at least twice as fast as using the GNU C++ linker).
// Also, init.c gives explicit control over the sequence of initialization.

// Programming convention: instead of using a global object (e,g, "Foo foo;"),
// use "Foo* foo;", create a function init_foo() in foo.c, and add a call
// to init_foo in init.cpp.

#include "prims/jni.h"

class init {
public:
    static jint init_globals();     // call constructors at startup (main Java thread)
    static void vm_init_globals();  // call constructors at startup (VM thread)
    static void exit_globals();     // call destructors before exit

    // my
    static void load_essential_classes();

    static bool is_init_completed();     // returns true when bootstrapping has completed
    static void set_init_completed();    // set basic init to completed

};

#endif //MINISPOT_INIT_H
