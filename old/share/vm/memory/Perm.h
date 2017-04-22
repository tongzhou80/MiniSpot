//
// Created by GentlyGuitar on 12/15/2016.
//

#ifndef MAGNOLIA_PERM_H
#define MAGNOLIA_PERM_H

#include <map>
#include "../oops/Symbol.h"
#include "../oops/JClass.h"

class JClass;
class JObject;
class JMethod;
class JField;
class ClassFile;
class ClassFileMethodInfo;

class LegitMethodName;

class Perm {
    static std::map<std::string, JClass*> _classdict_;
public:
    static JClass* createJClass(ClassFile*);
    static JMethod* createJMethod(ClassFileMethodInfo*, JClass*);
    static JField* createJField(ClassFileFieldInfo*, JClass*);
    void initPerm();
    static bool isClassLoaded(std::string name);
    static JClass* getClass(std::string name);
    static JMethod* getMethod(LegitMethodName* name);

};

#endif //MAGNOLIA_PERM_H
