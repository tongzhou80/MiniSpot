//
// Created by GentlyGuitar on 5/23/2017.
//

#include "classLoader.h"
#include "runtime/globals.h"
#include "utilities/ostream.h"

ClassLoader* ClassLoader::boot_loader = NULL;

void ClassLoader::init() {
    if (boot_loader == NULL) {
        boot_loader = new ClassLoader();
    }
    printf("done init boot classloader\n");
}

ClassLoader::ClassLoader() {
    if (OnlyUseBootLoader) {
        Loggers::todo << "todo: implement system properties such as java.class.path" << std::endl;
        std::string classpath = ".";
        _app_search_path.push_back(classpath);

    }
}

instanceKlassHandle ClassLoader::load_classfile(std::string name, Thread *__the_thread__) {

}

instanceKlassHandle ClassLoader::load_app_class(std::string name, Thread *__the_thread__) {

}
