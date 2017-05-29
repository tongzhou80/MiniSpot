#include <iostream>

#include "src/share/vm/prims/jni.h"

/* old main() */
//int main() {
//    VM* vm = new VM();
//    vm->start();
//    delete vm;
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}

/* Use jni to invoke main class's main method
 * argv should be parsed into JavaVMOption data structure and
 * be passed to JNI_CreateJavaVM. The class name part of argv
 * should be used to find main class. For now, we assume that
 * argv only contains class name.
 */
int main(int argc, char** argv) {
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
    const char* main_class = "Inc";
    /* invoke the main method using the JNI */
    jclass cls = env->FindClass(main_class);
//    jmethodID mid = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
//    env->CallStaticVoidMethod(cls, mid, 100);
    /* We are done. */
    // jvm->DestroyJavaVM();
}