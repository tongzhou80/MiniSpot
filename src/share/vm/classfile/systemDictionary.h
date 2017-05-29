//
// Created by GentlyGuitar on 5/23/2017.
//

#ifndef MINISPOT_SYSTEMDICTIONARY_H
#define MINISPOT_SYSTEMDICTIONARY_H

#include <map>
#include "runtime/handles.h"
#include <runtime/symbol.h>


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
private:
    //static std::map<std::pair<std::string, oop*>, InstanceKlass*> _placeholder_table;
    static std::map<std::string, SystemProperty*> _system_properties;
public:
    static bool init();
    static bool initialize_system_properties();

    static Klass* resolve_or_fail(Symbol& name, Handle loader);
    static SystemProperty* get_system_property(std::string key);
};

#endif //MINISPOT_SYSTEMDICTIONARY_H
