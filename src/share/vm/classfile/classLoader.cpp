//
// Created by GentlyGuitar on 5/23/2017.
//

#include "classfile/classLoader.h"
#include "classFile/classFile.h"
#include "runtime/globals.h"
#include "utilities/ostream.h"
#include "classfile/systemDictionary.h"

ClassLoader* ClassLoader::boot_loader = NULL;

void ClassLoader::init() {
    if (boot_loader == NULL) {
        boot_loader = new ClassLoader();
    }
    printf("done init boot classloader\n");
}

ClassLoader::ClassLoader() {
    if (OnlyUseBootLoader) {
        SystemProperty* classpath = SystemDictionary::get_system_property("java.class.path");
        assert(classpath != NULL, "class path system property not set");
        _app_search_path = classpath->val().split(':');
    }
}

instanceKlassHandle ClassLoader::load_classfile(Symbol& name) {

}

instanceKlassHandle ClassLoader::load_app_class(Symbol& name) {
    for (auto path: _app_search_path) {
        auto fullpath = name.prepend(path).append(".class").str();
        printf("should load %s\n", fullpath.c_str());
        ClassFile* classfile = parser.parse_from_file(fullpath);
        if (classfile) {

        }
    }

    return NULL;
}

bool ClassLoader::is_loaded(std::string key) {
    if (_loaded_klasses.find(key) == _loaded_klasses.end()) {
        return false;
    }
    else {
        return true;
    }
}

InstanceKlass* ClassLoader::get_class(std::string name) {
    if (is_loaded(name)) {
        return _loaded_klasses[name];
    }
    return NULL;
}