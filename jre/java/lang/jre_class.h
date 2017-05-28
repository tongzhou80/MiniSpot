//
// Created by GentlyGuitar on 5/26/2017.
//

#ifndef MINISPOT_JRE_CLASS_H
#define MINISPOT_JRE_CLASS_H


#include "jre_metadata.h"


class JRE_Class {
public:

    /* for internal parsing use */
    static std::vector<JREFieldDesc*> __fields__();
    static std::vector<JREFieldDesc*> __methods__();
};

#endif //MINISPOT_JRE_CLASS_H
