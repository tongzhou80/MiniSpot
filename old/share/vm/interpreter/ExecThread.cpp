//
// Created by GentlyGuitar on 12/12/2016.
//

#include "ExecThread.h"
#include "../VM.h"
#include "../classloader/ClassLoader.h"
#include "../oops/JMethod.h"
#include "../oops/JClass.h"
#include "../memory/JClassArea.h"
#include "../memory/Perm.h"
#include "../oops/Symbol.h"
#include "../interpreter/Interpreter.h"

ExecThread::ExecThread(VM* vm) {
    _vm = vm;
    _main_class_name = vm->classname();
    _stack_ = new ThreadStack();
}

ExecThread::~ExecThread() {
    delete _classloader_;

    if (PrintDestruction) {
        std::cout << "*** free an execution thread ***" << std::endl;
    }
}

void ExecThread::start() {
    _classloader_ = new ClassLoader();
    _classloader_->load(_main_class_name);
    _main_class = _classloader_->klass();
    callEntry();
}

void ExecThread::callEntry() {
//    _method = _main_class->entry();
//    createFrame();
//    _topframe->threadedInterpret();
    std::string entry_name = "main";
    std::string sig = "([Ljava/lang/String;)V";
    std::string class_name = _main_class->name();
    LegitMethodName* full_name_ = new LegitMethodName(class_name, entry_name, sig);

    //callMethod(full_name_);
    invokeStatic(full_name_);
}

void ExecThread::callMethod(LegitMethodName* name) {
    std::string clname = name->getClassPart();
    if (!Perm::isClassLoaded(clname)) {
        _classloader_->load(clname);
    }
    JMethod* m = Perm::getMethod(name);
    //m->
}

void ExecThread::invokeStatic(LegitMethodName* name) {
    std::string clname = name->getClassPart();
    if (!Perm::isClassLoaded(clname)) {
        _classloader_->load(clname);
    }

    JMethod* cur_m = Perm::getMethod(name);
    pushNewFrame(cur_m);
//    if (!cur_m->is_acc_static()) {
//        std::cerr << "Method " << name->str() << " is not static, exit." << std::endl;
//    }



    std::vector<Bytecode*> bytecodes = cur_m->bytecodes();
    for (int i = 0; i < 1; ++i) {
        if (bytecodes[i]->get_type() == Bytecode::BC_new) {
            ThreadedInterpreter::do_new(bytecodes[i], _topframe);
        }

    }
}


void ExecThread::invokeSpecial(int index) {

}

std::string ExecThread::resolveMethodRef(int index) {
    int class_index = ((ConstantMethodrefInfo*)(_cp->get(index, ConstantPool::ConstantMethodRef)))->class_index;

}

void ExecThread::pushNewFrame(JMethod* m) {
    _topframe = new MethodFrame(m);
    _stack_->push(_topframe);
}

void ThreadStack::push(MethodFrame* fr) {
    _stack_.push(fr);
}