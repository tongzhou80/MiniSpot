//
// Created by GentlyGuitar on 4/21/2017.
//

#include "thread.h"
#include "javaThread.h"
#include "osThread.h"
#include "../os.h"

// Threads
#ifdef __linux__
std::map<pthread_t, Thread*> Threads::_threads_table;

void Threads::register_thread(Thread * thread) {
    _threads_table[thread->osthread()->pthread_id()] = thread;

}
#endif

jint Threads::create_vm(JavaVMInitArgs *args, bool *canTryAgain) {
    // Attach the main thread to this os thread
    JavaThread* main_thread = new JavaThread();
    main_thread->set_thread_state(JavaThread::_thread_in_vm);


    os::create_thread(main_thread, os::java_thread);
}


// Thread

Thread::Thread() {

}

Thread::~Thread() {

}

void Thread::run() {
    ZPPL("I am running");
}


#ifdef __linux__

Thread* Thread::current() {
#ifdef ASSERT
    // This function is very high traffic. Define PARANOID to enable expensive
    // asserts.

#endif
    Thread* thread = Threads::get_pthread_by_id(pthread_self());
    assert(thread != NULL, "just checking");
    return thread;
}


#endif