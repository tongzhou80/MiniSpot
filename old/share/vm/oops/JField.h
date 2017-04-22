//
// Created by zhoutong1 on 12/25/16.
//

#ifndef MAGNOLIA_JFIELD_H
#define MAGNOLIA_JFIELD_H

#include <string>
#include "../global/TypeDef.h"
#include "../classloader/ClassFile.h"
#include "JClass.h"

class JFieldValue {
public:
    enum Type {
        BOOL,
        CHAR,
        BYTE,
        SHORT,
        INT,
        LONG,
        FLOAT,
        DOUBLE,
        OBJECTREF,
        ARRAYREF,
    };
};

class JField {
public:
    enum Type {
        BOOLEAN,
        CHAR,
        BYTE,
        SHORT,
        INT,
        LONG,
        FLOAT,
        DOUBLE,
        OBJECTREF,
        ARRAYREF,
    };
private:
    std::string _name;
    Type _type;
    u2 _real_size;
    u2 _heap_size;

    bool _acc_public;
    bool _acc_private;
    bool _acc_protected;
    bool _acc_static;
    bool _acc_final;
    bool _acc_volatile;
    bool _acc_transient;
    bool _acc_synthetic;
    bool _acc_enum;
public:
    JField(ClassFileFieldInfo*, JClass*);
    std::string name() { return _name; }
    Type type() { return _type; }
    u2 heap_size() { return _heap_size; }
};

#endif //MAGNOLIA_JFIELD_H
