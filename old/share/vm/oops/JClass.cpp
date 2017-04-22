//
// Created by GentlyGuitar on 12/13/2016.
//

#include "JClass.h"
#include "JMethod.h"
#include "../memory/Perm.h"
#include "JField.h"


JClass::JClass(ClassFile* clfile) {
    _classfile = clfile;
    _cp = clfile->cp_arr;
    init();
}

void JClass::init() {
    /* other init */

    initMeta();
    initFields();
    initMethods();
}

void JClass::initMeta() {
    _methods_cnt = _classfile->methods_count;
    _fields_cnt = _classfile->fields_count;
    int name_index = ((ConstantClassInfo*)_cp->get(_classfile->this_class, ConstantPool::ConstantClass))->name_index;
    _name = (char*)((ConstantUtf8Info*)(_cp->get(name_index, ConstantPool::ConstantUtf8)))->bytes;
}

void JClass::initFields() {
    for (int i = 0; i < _fields_cnt; i++) {
        JField* jfield = Perm::createJField(_classfile->fields[i], this);
        _fields_.push_back(jfield);
        _fields_size += jfield->heap_size();
    }
}

void JClass::initMethods() {
    for (int i = 0; i < _methods_cnt; i++) {
        JMethod* m = Perm::createJMethod(_classfile->methods[i], this);
        _methodmp_[m->innername()] = m;
        if (m->name() == "main") {
            _entry_method = m;
        }
    }
}

void JClass::constructFieldOffsetMap() {
    int off = 0;
    for (int i = 0; i < _fields_.size(); i++) {
        _offsetmp_[_fields_[i]->name()] = off;
        off += _fields_[i]->heap_size();
    }
}

JMethod* JClass::entry() {
    if (_entry_method == NULL) {
        std::cerr << "can't find class entry point, exit..." << std::endl;
        exit(0);
    }
    return _entry_method;
}

JMethod* JClass::fetchMethod(std::string name) {
    if (_methodmp_.find(name) == _methodmp_.end()) {
        std::cerr << "Method " << _name << "." << name << " not found, exit." << std::endl;
        exit(0);
    }
    JMethod* m = _methodmp_[name];
    if (!m->isReady()) {
        m->cookMethod();
    }

    return m;
}
