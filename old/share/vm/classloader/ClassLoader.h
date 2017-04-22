//
// Created by GentlyGuitar on 12/13/2016.
//

#ifndef MAGNOLIA_CLASSLOADER_H
#define MAGNOLIA_CLASSLOADER_H

#include "ClassFile.h"
#include "../oops/JClass.h"
#include <vector>

class JClass;

class ClassLoader {
    std::string _classpath;
    std::string _classname;
    ClassParser* _classparser_;
    ClassFile* _classfile;
    JClass* _klass;
    std::vector<std::string> _classpaths_;

public:
    ClassLoader();
    ~ClassLoader();
    void initClasspaths();
    void load(std::string);
    //bool isLoaded(std::string);
    std::string resolveClassPath(std::string name);
    void loadToVM();
    ClassFile* classfile() { return _classfile; }
    JClass* klass() { return _klass; }

    void parseBytecode();
};

#endif //MAGNOLIA_CLASSLOADER_H
