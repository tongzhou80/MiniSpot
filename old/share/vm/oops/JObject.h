//
// Created by zhoutong1 on 12/22/16.
//

#ifndef MAGNOLIA_JOBJECT_H
#define MAGNOLIA_JOBJECT_H

#include <string>
#include "ObjectHeader.h"
#include "../global/TypeDef.h"

class ObjectHeader;

class JObject {
    ObjectHeader* _header_;
    int _body_len;
    u1* _body;
public:
    JObject(JClass*);
};

#endif //MAGNOLIA_JOBJECT_H
