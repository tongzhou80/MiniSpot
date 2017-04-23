//
// Created by GentlyGuitar on 4/21/2017.
//

#include "thread.h"

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
    main_thread->set_thread_state(_thread_in_vm);
}


// Thread

Thread::Thread() {

}

Thread::~Thread() {

}

void Thread::run() {
    ZPPL("I am running");
}