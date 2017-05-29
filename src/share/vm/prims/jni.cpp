//
// Created by zhoutong1 on 1/1/17.
//

#include <iostream>
#include <utilities/ostream.h>
#include "jni.h"
#include "prims/jvm.h"
#include "utilities/debug.h"
#include "runtime/threads/thread.h"
#include "runtime/threads/javaThread.h"
#include "runtime/symbol.h"

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

jint jni_GetVersion(JNIEnv* env) {
    return (jint)1;
}

jclass jni_FindClass(JNIEnv *env, const char *name) {

    InstanceKlass* calling_class = JavaThread::current()->caller_class();
    if (calling_class) {
        Loggers::todo << "todo: jni_FindClass needs to use caller class's loader to load the callee class" << std::endl;
    }
    else {
        Symbol classname(name);
        return find_class_from_class_loader(classname, NULL); // ignore loader param for now
    }
}


// Structure containing all jni functions
struct JNINativeInterface_ jni_NativeInterface = {
        NULL,
        NULL,
        NULL,

        NULL,

        jni_GetVersion,

        //jni_DefineClass,
        jni_FindClass
};


// Returns the function structure
struct JNINativeInterface_* jni_functions() {
    return &jni_NativeInterface;
}