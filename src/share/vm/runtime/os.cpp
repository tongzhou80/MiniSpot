//
// Created by tzhou on 4/22/17.
//

#include "os.h"
#include <pthread.h>
#include "thread.h"


#ifdef __linux__

#include <sys/syscall.h>
#include <unistd.h>

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
    thread->osthread()->set_thread_id(os::gettid());

    Monitor* sync = osthread->startThread_lock();

    // handshaking with parent thread
    {
        MutexLockerEx ml(sync, Mutex::_no_safepoint_check_flag);

        // notify parent thread
        osthread->set_state(INITIALIZED);
        sync->notify_all();

        // wait until os::start_thread()
        while (osthread->get_state() == INITIALIZED) {
            sync->wait(Mutex::_no_safepoint_check_flag);
        }
    }

    // call one more level start routine
    thread->run();

    return 0;
}

bool os::create_thread(Thread* thread, ThreadType threadType, int stack_size) {
    OSThread* osthread = new OSThread();
    osthread->set_thread_type(threadType);
    osthread->set_state(ALLOCATED);
    thread->set_osthread(osthread);

    pthread_t tid;
    int ret;
    printf("In main: creating thread\n");
    ret =  pthread_create(&tid, NULL, java_start, thread);

    if (ret != 0) {
        /* error handling */
    }

    osthread->set_pthread_id(tid);

//    // Wait until child thread is either initialized or aborted
//    {
//        Monitor* sync_with_child = osthread->startThread_lock();
//        MutexLockerEx ml(sync_with_child, Mutex::_no_safepoint_check_flag);
//        while ((state = osthread->get_state()) == ALLOCATED) {
//            sync_with_child->wait(Mutex::_no_safepoint_check_flag);
//        }
//    }

    return true;
}

#endif