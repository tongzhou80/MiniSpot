//
// Created by tzhou on 4/20/17.
//

#ifndef MAGNOLIA_THREAD_H
#define MAGNOLIA_THREAD_H

#include "../native/JNI.h"

class Threads {
    static jint create_vm(JavaVMInitArgs* args, bool* canTryAgain);
    static bool destroy_vm();

};

#endif //MAGNOLIA_THREAD_H
