//
// Created by GentlyGuitar on 5/23/2017.
//

#ifndef MINISPOT_SYSTEMDICTIONARY_H
#define MINISPOT_SYSTEMDICTIONARY_H

#include <map>

class oop;
class InstanceKlass;

class SystemDictionary {
private:
    std::map<std::pair<std::string, oop>, InstanceKlass*> placeholder_table;
public:
    static bool init();
};

#endif //MINISPOT_SYSTEMDICTIONARY_H
