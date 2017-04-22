//
// Created by GentlyGuitar on 12/13/2016.
//

#ifndef MAGNOLIA_JCLASS_H
#define MAGNOLIA_JCLASS_H

#include "../global/TypeDef.h"
#include "../classloader/ClassFile.h"
#include "JMethod.h"
#include "JField.h"
//#include "JMethod.h" // cause circular include, just declare JMethod in this file
//#include "../interpreter/ExecThread.h"   // cause include loop

class JMethod;
class JField;

class JClass {
    ClassFile* _classfile;
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;


    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2* interfaces; // index into constant pool


    float java_version;

    bool acc_public;
    bool acc_final;
    bool acc_super;
    bool acc_interface;
    bool acc_abstract;
    bool acc_synthetic;
    bool acc_annotation;
    bool acc_enum;

    std::string _name;
    std::string _signature;
    int _methods_cnt;
    int _fields_cnt;
    int _fields_size;
    JMethod* _entry_method;
    std::map<std::string, JMethod*> _methodmp_;
    std::map<std::string, int> _offsetmp_;
    std::vector<JField*> _fields_;
    ConstantPool* _cp;
public:
    JClass(ClassFile* classfile);

    JMethod* entry();
    JMethod* fetchMethod(std::string name);

    void init();
    void initMeta();
    void initMethods();
    void initFields();
    void constructFieldOffsetMap();

    ConstantPool* constantPool() { return _cp; }
    std::string name() { return _name; }
    std::string signature() { return _signature; }
    int fields_size() { return _fields_size; }
};

#endif //MAGNOLIA_JCLASS_H
