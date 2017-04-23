//
// Created by zhoutong1 on 1/1/17.
//

#include <iostream>
#include "jni.h"
#include "../utilities/debug.h"
#include "../runtime/thread.h"


JavaVM main_vm;

//struct JNIInvokeInterface
//{
//    jint (*GetEnv)(JavaVM*, void**, jint);
//    jint (*AttachCurrentThreadAsDaemon)(JavaVM*, JNIEnv**, void*);
//};

//struct JavaVM
//{
//    const struct JNIInvokeInterface* functions;
//#if defined(__cplusplus)
//    jint GetEnv(void** env, jint version)
//    { return functions->GetEnv(this, env, version); }
//    jint AttachCurrentThreadAsDaemon(JNIEnv** p_env, void* thr_args)
//    { return functions->AttachCurrentThreadAsDaemon(this, p_env, thr_args); }
//#endif /*__cplusplus*/
//};

static jint JNI_CreateJavaVM_inner(JavaVM **vm, void **penv, void *args) {
    jint result = JNI_ERR;
    bool can_try_again = true;
    result = Threads::create_vm((JavaVMInitArgs*) args, &can_try_again);
    if (result == JNI_OK) {
        JavaThread *thread = JavaThread::current();
        /* thread is thread_in_vm here */

        *vm = (JavaVM *)(&main_vm);
        *(JNIEnv**)penv = thread->jni_environment();
    }
}

jint JNI_CreateJavaVM(JavaVM **p_vm, void **p_env, void *vm_args) {
    return JNI_CreateJavaVM_inner(p_vm, p_env, vm_args);
}


//jint DestroyJavaVM(JavaVM *vm) {
//    delete vm;
//}

//JavaVM* create_vm(JavaVMInitArgs*) {
////    JavaVM* vm = new JavaVM();
////    vm->parseArgs();
////    SysUtil::init_bcdict();
////    ThreadedInterpreter::initRoutineDict();
//    //vm->spawnExecThread();
//    return vm;
//}