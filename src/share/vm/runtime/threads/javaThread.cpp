//
// Created by tzhou on 4/23/17.
//

#include "javaThread.h"



// Inline implementation of JavaThread::current
JavaThread* JavaThread::current() {
    return (JavaThread*)Thread::current();
}
