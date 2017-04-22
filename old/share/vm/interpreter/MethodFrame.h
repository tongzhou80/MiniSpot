//
// Created by GentlyGuitar on 12/12/2016.
//

#ifndef MAGNOLIA_METHODFRAME_H
#define MAGNOLIA_METHODFRAME_H

#include <stack>
#include "../classloader/ClassFile.h"
#include "../oops/JMethod.h"
#include "ExecThread.h"

class JMethod;
class ExecThread;
class OperandStack;
class JValue;

class OperandStack {
    std::stack<JValue*> stack;
public:
    bool is_empty() { return stack.empty(); }
    JValue* top() {
        if (is_empty()) {
            return NULL;
        }
        else {
            return stack.top();
        }
    }
    JValue* pop() {
        if (is_empty()) {
            return NULL;
        }
        else {
            JValue* rv = top();
            stack.pop();
            return rv;
        }
    }
    bool pop(JValue* receiver) { receiver = pop(); }
    void push(JValue* v) { stack.push(v); }
};

class MethodFrame {
    OperandStack* _stack_;
    JValue** _locals_;
    ConstantPool* _cp;
    JMethod* _method;
    ExecThread* _thread;
    int _max_stack_depth;
    int _max_locals;
    int _code_len;
    int _bci; // byte pointer into raw bytecode

public:
    MethodFrame(JMethod*);

    OperandStack* stack() { return _stack_; }
    JMethod* method() { return _method; }
    ExecThread* thread() { return _thread; }
    int bci() { return _bci; }
    ConstantPool* cp() { return _cp; }
    int incBytep(int i) { _bci += i; }
    JValue* get_local(int i) { return _locals_[i]; }
    void load(int i) { _stack_->push(_locals_[i]); }
    void store(int i) { _stack_->pop(_locals_[i]); }
    void push(JValue* v) { _stack_->push(v); }

    void threadedInterpret();

    ~MethodFrame();

    void ts_iadd();

//    /* interpretation */
//    void do_new();
};

union JValueData {
    bool b;
    short s;
    int i;
    long l;
};

class JValue {
public:
    enum Type {
        Short, Int, Long
    };

    template<typename T>
    JValue(T v);
private:
    Type type;
    union JValueData data;
};

template<typename T>
JValue::JValue(T v) {
    if (std::is_same<T, int>::value) {
        data.i = v;
    }
}

#endif //MAGNOLIA_METHODFRAME_H
