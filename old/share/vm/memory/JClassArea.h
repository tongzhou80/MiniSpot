//
// Created by GentlyGuitar on 12/15/2016.
//

#ifndef MAGNOLIA_JCLASSAREA_H
#define MAGNOLIA_JCLASSAREA_H

#include <map>

class JClass;
class ClassFile;

/* holds all JClass instances */
class JClassArea {
    std::map<std::string, JClass*> _classdict_;
public:
    JClassArea();
    ~JClassArea();
    JClass* createJClass(ClassFile*);
};

#endif //MAGNOLIA_JCLASSAREA_H
