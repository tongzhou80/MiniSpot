//
// Created by GentlyGuitar on 12/15/2016.
//

#include <cassert>
#include "Perm.h"
#include "../oops/JClass.h"
#include "../oops/JMethod.h"
#include "../oops/JField.h"
#include "../oops/Symbol.h"
#include "../classloader/ClassFile.h"

std::map<std::string, JClass*> Perm::_classdict_;



JClass* Perm::createJClass(ClassFile* classfile) {
    JClass* klass = new JClass(classfile);
    //_classdict_.insert(std::make_pair(klass->name(), klass));
    _classdict_[klass->name()] = klass;
    if (PrintClassCreation) {
        std::cout << "create class " << klass->name() << std::endl;
    }
    return klass;
}

JMethod* Perm::createJMethod(ClassFileMethodInfo* minfo, JClass* jc) {
    JMethod* m = new JMethod(minfo, jc);
    return m;
}

bool Perm::isClassLoaded(std::string name) {
    if (_classdict_.find(name) == _classdict_.end()) {
        return false;
    }
    else {
        return true;
    }
}

JClass* Perm::getClass(std::string name) {
    if (isClassLoaded(name)) {
        return _classdict_[name];
    }
    else {
        return NULL;
    }
}

/* a class should be already loaded before calling this method */
JMethod* Perm::getMethod(LegitMethodName* name) {
    assert(isClassLoaded(name->getClassPart()));
    JClass* jc = getClass(name->getClassPart());
    return jc->fetchMethod(name->getMethodPart());
}

JField* Perm::createJField(ClassFileFieldInfo* finfo, JClass* klass) {
    JField* field = new JField(finfo, klass);
    return field;
}
