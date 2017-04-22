//
// Created by zhoutong1 on 12/22/16.
//

#ifndef MAGNOLIA_OBJECTHEADER_H
#define MAGNOLIA_OBJECTHEADER_H

#include "JClass.h"

class JClass;

class ObjectHeader {
    JClass* _klass;
public:
    JClass* klass();
    JClass* setJclass(JClass* cl) { _klass = cl; }
};

#endif //MAGNOLIA_OBJECTHEADER_H
