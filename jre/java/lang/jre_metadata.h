//
// Created by GentlyGuitar on 5/26/2017.
//

#ifndef MINISPOT_JRE_METADATA_H
#define MINISPOT_JRE_METADATA_H


#include <string>
#include <vector>
#include <prims/jni.h>

/* represent fields and method */
struct JREFieldDesc {
    std::string descriptor;
    std::vector<std::string> flags;
};

struct JREClassDesc {

};

#endif //MINISPOT_JRE_METADATA_H
