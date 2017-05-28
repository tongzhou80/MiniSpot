//
// Created by GentlyGuitar on 5/27/2017.
//

#ifndef MINISPOT_ARGUMENTS_H
#define MINISPOT_ARGUMENTS_H

#include <string>
#include <map>
#include <vector>
#include "symbol.h"

class SystemProperty;


class Arguments {
public:
    // static std::map<std::string, SystemProperty*> system_properties; // move to systemDictionary to avoid some complicated include relations
    static Symbol main_class;
    static std::vector<std::string> arguments;
};

#endif //MINISPOT_ARGUMENTS_H
