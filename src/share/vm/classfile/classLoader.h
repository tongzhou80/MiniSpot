//
// Created by GentlyGuitar on 5/23/2017.
//

#ifndef MINISPOT_CLASSLOADER_H
#define MINISPOT_CLASSLOADER_H

#include <string>
#include <vector>
#include "utilities/exceptions.h"
#include "runtime/handles.h"
#include "runtime/symbol.h"

/* the bootstrap classloader */
class ClassLoader {
private:
    std::vector<std::string> _search_path;
public:
    static ClassLoader* boot_loader;
    static void init();
    static void destroy();

    ClassLoader();


    instanceKlassHandle load_classfile(Symbol* h_name, TRAPS);
};

#endif //MINISPOT_CLASSLOADER_H
