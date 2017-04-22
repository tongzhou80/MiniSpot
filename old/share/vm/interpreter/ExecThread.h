//
// Created by GentlyGuitar on 12/12/2016.
//

#ifndef MAGNOLIA_EXECTHREAD_H
#define MAGNOLIA_EXECTHREAD_H

#include "MethodFrame.h"
#include "../oops/Symbol.h"
#include <stack>

/* implemented destructors */
class ExecThread;
class VM;
class ClassLoader;


/* not yet */
class ThreadStack;
class JMethod;
class JClass;
class LegitMethodName;


/* not need */

class ThreadStack {
    std::stack<MethodFrame*> _stack_;
    MethodFrame* _topframe;
public:

    MethodFrame* top() { return _topframe; }
    void push(MethodFrame* fr);
    MethodFrame* pop();
};

class ExecThread {
    VM* _vm;
    ThreadStack* _stack_;
    MethodFrame* _topframe;
    ConstantPool* _cp;
    u4 _pc;

    //std::string _main_class_path;
    std::string _main_class_name;
    ClassLoader* _classloader_;

    /* assigned from other objects */
    JMethod* _method;
    JClass* _main_class;

    /* to add: native stack */

public:
    ExecThread(VM* vm);
    ~ExecThread();
    void init();
    u4 pc();
    JMethod* method();
    void start();
    void callEntry();
    void callMethod(LegitMethodName* name);
    void execMethod();
    void threadedInterpret();
    std::string resolveMethodRef(int index);
    void invokeSpecial(int index);
    void invokeStatic(int index);
    void invokeStatic(LegitMethodName* name);
    void pushNewFrame(JMethod*);

};



#endif //MAGNOLIA_THREAD_H
