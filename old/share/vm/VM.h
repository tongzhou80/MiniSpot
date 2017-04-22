//
// Created by GentlyGuitar on 12/14/2016.
//

#ifndef MAGNOLIA_VM_H
#define MAGNOLIA_VM_H

#include <thread>
#include <string>
#include "native/JNI.h"



class ClassLoader;
class JClassArea;
class ExecThread;

class VM {
    std::string _classname;
    //JClassArea* _classarea_;

public:
    VM();
    ~VM();
    void parseArgs();
    void initPerm();
    void spawnGC();
    void spawnExecThread();
    void start();

    std::string classname() { return _classname; }
    //JClassArea* classarea() { return _classarea_; }
};

#endif //MAGNOLIA_VM_H
