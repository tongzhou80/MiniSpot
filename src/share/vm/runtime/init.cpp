//
// Created by tzhou on 4/23/17.
//

#include <classfile/classLoader.h>
#include "init.h"
#include "memory/universe.h"
#include "utilities/ostream.h"
#include "classfile/systemDictionary.h"

void init::vm_init_globals() {

}

jint init::init_globals() {
    Loggers::init();
    Universe::init();
    SystemDictionary::init();
    ClassLoader::init();
}