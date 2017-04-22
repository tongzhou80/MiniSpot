//
// Created by GentlyGuitar on 12/15/2016.
//

#include "JClassArea.h"
#include "../oops/JClass.h"

JClassArea::JClassArea() {

}

JClass* JClassArea::createJClass(ClassFile * classFile) {
    JClass* klass = new JClass(classFile);
    //_classdict_.insert(std::make_pair(klass->name(), klass));
    _classdict_[klass->name()] = klass;
    if (PrintClassCreation) {
        std::cout << "create class " << klass->name() << std::endl;
    }
    return klass;
}

JClassArea::~JClassArea() {
    /* delete dict */
}
