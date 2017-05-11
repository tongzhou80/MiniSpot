//
// Created by tzhou on 4/22/17.
//

#include "os.h"
#include <pthread.h>
#include "threads/thread.h"
#include "threads/osThread.h"
#include "globals.h"

#ifdef __linux__

#include <sys/syscall.h>
#include <unistd.h>
#include "mutex.h"

/* For some reason, gettid is not implemented in glibc */
pid_t os::gettid() {
    int rslt = syscall(SYS_gettid);
    assert(rslt != -1, "must be.");
    return (pid_t)rslt;

    /* or */
    return syscall( __NR_gettid );
}

//////////////////////////////////////////////////////////////////////////////
// create new thread

// Thread start routine for all newly created threads
static void *java_start(Thread *thread) {
    Threads::register_thread(thread);
    OSThread* osthread = thread->osthread();
    osthread->set_thread_id(os::gettid());

    Monitor* sync = osthread->startThread_lock();

    // handshaking with parent thread
    {
        sync->lock();
        // notify parent thread
        osthread->set_state(OSThread::INITIALIZED);
        sync->signal_all();
        sync->unlock();
        //pthread_cond_broadcast(sync->cond()); // notify should be enough, but broadcast just in case
        //pthread_mutex_unlock(sync->mutex());
    }

    // wait until os::start_thread()
    if (PrintThreadCreation) {
        printf("thread " PID_FORMAT " has initialized, wait until os::start_thread()\n", osthread->pthread_id());
    }
    while (osthread->get_state() == OSThread::INITIALIZED) {
        sync->wait();
        //pthread_cond_wait(sync->cond(), sync->mutex());
    }


//    // handshaking with parent thread
//    {
//        MutexLockerEx ml(sync, Mutex::_no_safepoint_check_flag);
//
//        // notify parent thread
//        osthread->set_state(OSThread::INITIALIZED);
//        sync->notify_all();
//
//        // wait until os::start_thread()
//        while (osthread->get_state() == OSThread::INITIALIZED) {
//            sync->wait(Mutex::_no_safepoint_check_flag);
//        }
//    }

    // call one more level start routine
    thread->run();

    return 0;
}

bool os::create_thread(Thread* thread, ThreadType threadType, int stack_size) {
    OSThread* osthread = new OSThread();
    osthread->set_thread_type(threadType);
    osthread->set_state(OSThread::ALLOCATED);
    thread->set_osthread(osthread);

    pthread_t tid;
    int ret =  pthread_create(&tid, NULL, (void* (*)(void*)) java_start, thread);
    if (PrintThreadCreation) {
        printf("created %s, pthread id: " PID_FORMAT "\n", thread_type_str(threadType), tid);
    }


    if (ret != 0) {
        /* error handling */
    }

    osthread->set_pthread_id(tid);

    // Wait until child thread is either initialized or aborted
    /* the curly bracket is not necessary(as it is in HotSpot's code), just to make critical clearer */
    {
        Monitor* sync_with_child = osthread->startThread_lock();
        sync_with_child->lock();
        //pthread_mutex_lock(sync_with_child->mutex());
        while (osthread->get_state() == OSThread::ALLOCATED) {
            sync_with_child->wait();
            //pthread_cond_wait(sync_with_child->cond(), sync_with_child->mutex());
        }
        sync_with_child->unlock();
        //pthread_mutex_unlock(osthread->startThread_lock()->mutex());

    }


//    // Wait until child thread is either initialized or aborted
//    {
//        Monitor* sync_with_child = osthread->startThread_lock();
//        MutexLockerEx ml(sync_with_child, Mutex::_no_safepoint_check_flag);
//        while ((state = osthread->get_state()) == OSThread::ALLOCATED) {
//            sync_with_child->wait(Mutex::_no_safepoint_check_flag);
//        }
//    }

    return true;
}

// The INITIALIZED state is distinguished from the SUSPENDED state because the
// conditions in which a thread is first started are different from those in which
// a suspension is resumed.  These differences make it hard for us to apply the
// tougher checks when starting threads that we want to do when resuming them.
// However, when start_thread is called as a result of Thread.start, on a Java
// thread, the operation is synchronized on the Java Thread object.  So there
// cannot be a race to start the thread and hence for the thread to exit while
// we are working on it.  Non-Java threads that start Java threads either have
// to do so in a context in which races are impossible, or should do appropriate
// locking.
void os::start_thread(Thread *thread) {
    OSThread* osthread = thread->osthread();
    Monitor* sync_with_child = osthread->startThread_lock();
    {
        sync_with_child->lock();
        //pthread_mutex_lock(sync_with_child->mutex());
        osthread->set_state(OSThread::RUNNABLE);
        sync_with_child->signal();
        //pthread_cond_signal(sync_with_child->cond());
        sync_with_child->unlock();
        //pthread_mutex_unlock(sync_with_child->mutex());
    }
}

#endif