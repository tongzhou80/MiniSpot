//
// Created by GentlyGuitar on 5/23/2017.
//

#ifndef MINISPOT_SYSTEMDICTIONARY_H
#define MINISPOT_SYSTEMDICTIONARY_H

#include <map>
#include <oops/klass.h>
#include "runtime/handles.h"
#include <runtime/symbol.h>

class oop;
class InstanceKlass;

class SystemProperty {
    Symbol _key;
    Symbol _val;
public:
    SystemProperty(const char* k, const char* v) { _key = k, _val = v; }
    Symbol& key() { return _key; }
    Symbol& val() { return _val; }
};


class SystemDictionary {
public:
    static bool init();
    static bool initialize_system_properties();

    static std::map<std::pair<std::string, oop>, InstanceKlass*> placeholder_table;
    static std::map<std::string, SystemProperty*> system_properties;
    static bool load_main_class();
    static Klass* resolve_or_fail(Symbol* name, Handle loader);

};

#endif //MINISPOT_SYSTEMDICTIONARY_H
