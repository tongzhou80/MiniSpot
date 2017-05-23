//
// Created by GentlyGuitar on 5/23/2017.
//

#include "classLoader.h"

ClassLoader* ClassLoader::boot_loader = NULL;

void ClassLoader::init() {
    if (boot_loader == NULL) {
        boot_loader = new ClassLoader();
    }
    printf("done init classloader\n");
}

ClassLoader::ClassLoader() {

}

instanceKlassHandle ClassLoader::load_classfile(Symbol *h_name, Thread *__the_thread__) {

}