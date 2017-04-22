#include <iostream>
#include "global/TypeDef.h"
#include "classloader/ClassFile.h"
#include "classloader/ClassLoader.h"
#include "VM.h"
#include "VM.h"
#include "native/JNI.h"

/* old main() */
//int main() {
//    VM* vm = new VM();
//    vm->start();
//    delete vm;
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}

/* Use jni to invoke main class's main method */
int main() {
    JavaVM *jvm;       /* denotes a Java VM */
    JNIEnv *env;       /* pointer to native method interface */
    JavaVMInitArgs vm_args; /* JDK/JRE 6 VM initialization arguments */
    JavaVMOption* options = new JavaVMOption[1];
    options[0].optionString = "-Djava.class.path=/usr/lib/java";
    vm_args.version = 0; /* not sure what value this arg should be */
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;
    /* load and initialize a Java VM, return a JNI interface
     * pointer in env */
    JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    delete options;
    /* invoke the main method using the JNI */
    jclass cls = env->FindClass("Inc");
    jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
    env->CallStaticVoidMethod(cls, mid, 100);
    /* We are done. */
    jvm->DestroyJavaVM();
}