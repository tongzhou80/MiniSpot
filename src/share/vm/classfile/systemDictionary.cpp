//
// Created by GentlyGuitar on 5/23/2017.
//

#include "systemDictionary.h"

bool SystemDictionary::initialize_system_properties() {
    SystemProperty* aProperty = new SystemProperty("java.class.path", ".");
    system_properties["java.class.path"] = aProperty;
}

bool SystemDictionary::init() {

}

Klass* SystemDictionary::resolve_or_fail(Symbol *name, Handle loader) {

}