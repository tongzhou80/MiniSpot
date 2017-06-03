//
// Created by GentlyGuitar on 5/23/2017.
//

#include "systemDictionary.h"
#include "utilities/ostream.h"
#include "classfile/classLoader.h"

std::map<std::string, SystemProperty*> SystemDictionary::_system_properties;
std::map<char, JBCMeta*> SystemDictionary::bcdict;

/* argument parsing should override these properties */
bool SystemDictionary::initialize_system_properties() {
    //SystemProperty* aProperty = new SystemProperty("java.class.path", "./");
    SystemProperty* aProperty = new SystemProperty("java.class.path", "../src/test/"); // hard-wired
    _system_properties["java.class.path"] = aProperty;
}

void SystemDictionary::initialize_bcdict() {
    bcdict[0xbb] = new JBCMeta(Bytecode::BC_new, "new", 2);
    bcdict[0x59] = new JBCMeta(Bytecode::BC_dup, "dup", 0);
    bcdict[0xb7] = new JBCMeta(Bytecode::BC_invokespecial, "invokespecial", 2);
}

bool SystemDictionary::init() {
    initialize_system_properties();
    initialize_bcdict();
}

/* look for the class in the table, if not exist, try to load from classpath */
Klass* SystemDictionary::resolve_or_fail(Symbol& name, Handle loader) {
    Loggers::todo << "todo: SystemDictionary::resolve_or_fail, not to use boot loader load anything\n";
    ClassLoader* ld = ClassLoader::boot_loader;
    if (ld->is_loaded(name.str())) {
        return ld->get_class(name.str());
    }

    return ld->load_app_class(name);
    /* Use boot loader for now */
}

SystemProperty* SystemDictionary::get_system_property(std::string key) {
    if (_system_properties.find(key) == _system_properties.end()) {
        return NULL;
    }
    else {
        return _system_properties[key];
    }
}