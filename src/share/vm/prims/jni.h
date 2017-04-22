//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_JNI_H
#define MINISPOT_JNI_H


#include <stdio.h>
#include <cstdarg>

/*
 * jboolean constants
 */

#define JNI_FALSE 0
#define JNI_TRUE 1

/*
 * possible return values for JNI functions.
 */

#define JNI_OK           0                 /* success */
#define JNI_ERR          (-1)              /* unknown error */
#define JNI_EDETACHED    (-2)              /* thread detached from the VM */
#define JNI_EVERSION     (-3)              /* JNI version error */
#define JNI_ENOMEM       (-4)              /* not enough memory */
#define JNI_EEXIST       (-5)              /* VM already created */
#define JNI_EINVAL       (-6)              /* invalid arguments */

class JavaVM;
class JavaVMInitArgs;

typedef int jint;
typedef jint jsize;
typedef bool jboolean;

typedef void* jobject;
typedef jobject jclass;
typedef jobject jthrowable;
typedef jobject jstring;
typedef jobject jarray;

typedef int jmethodID;

struct JavaVMInitArgs {
    jint version;
    jint nOptions;
    JavaVMOption *options;
    jboolean ignoreUnrecognized;
};

struct JavaVMOption {
    char *optionString;  /* the option as a string in the default platform encoding */
    void *extraInfo;
};

typedef struct JavaVMAttachArgs {
    jint version;

    char *name;
    jobject group;
};

class JNIEnv;
class JavaVM;


/* JNICALL should be defined on some platform such as Windows */
#define JNICALL

struct JNIEnv
{
    JNINativeInterface_* functions; /* compatible with C style JNIEnv */
#if defined(__cplusplus)


    jint GetVersion() {
        return functions->GetVersion(this);
    }

    jclass FindClass(const char *name) {
        return functions->FindClass(this, name);
    }

    jmethodID GetMethodID(jclass clazz, const char* name, const char* sig) {
        return functions->GetMethodID(this, clazz, name, sig);
    }

    jmethodID GetStaticMethodID(jclass clazz, const char* name, const char* sig) {
        return functions->GetMethodID(this, clazz, name, sig);
    }

    void CallStaticVoidMethod(jclass cls, jmethodID methodID, ...) {
        va_list args;
        va_start(args,methodID);
        functions->CallStaticVoidMethodV(this,cls,methodID,args);
        va_end(args);
    }

    void CallStaticVoidMethodV(jclass cls, jmethodID methodID,
                               va_list args) {
        functions->CallStaticVoidMethodV(this,cls,methodID,args);
    }


#endif /*__cplusplus*/
};

struct JNINativeInterface_ {
    void *reserved0;
    void *reserved1;
    void *reserved2;

    void *reserved3;

    jint (JNICALL *GetVersion)(JNIEnv *env);

    jclass (JNICALL *FindClass)
            (JNIEnv *env, const char *name);

    jmethodID (JNICALL *GetMethodID)
            (JNIEnv *env, jclass clazz, const char *name, const char *sig);

    jmethodID (JNICALL *GetStaticMethodID)
            (JNIEnv *env, jclass clazz, const char *name, const char *sig);

    void (JNICALL *CallStaticVoidMethod)
            (JNIEnv *env, jclass cls, jmethodID methodID, ...);

    void (JNICALL *CallStaticVoidMethodV)
            (JNIEnv *env, jclass cls, jmethodID methodID, va_list args);

    /* and other methods */
};

/* Each function is accessible at a fixed offset through the JNIEnv argument.
 * The JNIEnv type is a pointer to a structure storing all JNI function pointers.
 *
 */

struct JNIInvokeInterface_ {
    void *reserved0;
    void *reserved1;
    void *reserved2;

    jint (JNICALL *DestroyJavaVM)(JavaVM *vm);

    jint (JNICALL *AttachCurrentThread)(JavaVM *vm, void **penv, void *args);

    jint (JNICALL *DetachCurrentThread)(JavaVM *vm);

    jint (JNICALL *GetEnv)(JavaVM *vm, void **penv, jint version);

    jint (JNICALL *AttachCurrentThreadAsDaemon)(JavaVM *vm, void **penv, void *args);
};

struct JavaVM {
    const struct JNIInvokeInterface_ *functions;
#ifdef __cplusplus

    jint DestroyJavaVM() {
        return functions->DestroyJavaVM(this);
    }
    jint AttachCurrentThread(void **penv, void *args) {
        return functions->AttachCurrentThread(this, penv, args);
    }
    jint DetachCurrentThread() {
        return functions->DetachCurrentThread(this);
    }

    jint GetEnv(void **penv, jint version) {
        return functions->GetEnv(this, penv, version);
    }
    jint AttachCurrentThreadAsDaemon(void **penv, void *args) {
        return functions->AttachCurrentThreadAsDaemon(this, penv, args);
    }
#endif
};


/* functions interface */
jint JNI_CreateJavaVM(JavaVM **p_vm, void **p_env, void *vm_args);
jint DestroyJavaVM(JavaVM *vm);
jint GetEnv(JavaVM *vm, void **env, jint version);

/* helper functions */
JavaVM* createVM(JavaVMInitArgs*);

#endif //MINISPOT_JNI_H
