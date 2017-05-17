//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_THREAD_H
#define MINISPOT_THREAD_H

#include <iostream>
#include <map>
#include "utilities/debug.h"
#include "prims/jni.h"
#include "utilities/globalDefinitions.h"

class OSThread;

// Class hierarchy
// - Thread
//   - NamedThread
//     - VMThread
//     - ConcurrentGCThread
//     - WorkerThread
//       - GangWorker
//       - GCTaskThread
//   - JavaThread
//   - WatcherThread


class Thread {
public:
    OSThread* _osthread;

public:
    // Constructor
    Thread();
    virtual ~Thread();

    // initializtion
    void initialize_thread_local_storage();

    // thread entry point
    virtual void run();

    // OSThread
    OSThread* osthread()  { return _osthread; }
    void set_osthread(OSThread* osThread)  { _osthread = osThread; }

    // Testers
    virtual bool is_VM_thread()       const            { return false; }
    virtual bool is_Java_thread()     const            { return false; }
    virtual bool is_Compiler_thread() const            { return false; }
    virtual bool is_Code_cache_sweeper_thread() const  { return false; }
    virtual bool is_hidden_from_external_view() const  { return false; }
    virtual bool is_jvmti_agent_thread() const         { return false; }
    // True iff the thread can perform GC operations at a safepoint.
    // Generally will be true only of VM thread and parallel GC WorkGang
    // threads.
    virtual bool is_GC_task_thread() const             { return false; }
    virtual bool is_Watcher_thread() const             { return false; }
    virtual bool is_Sampler_thread() const             { return false; }
    virtual bool is_ConcurrentGC_thread() const        { return false; }
    virtual bool is_Named_thread() const               { return false; }
    virtual bool is_Worker_thread() const              { return false; }

    virtual char* name() const { return (char*)"Unknown thread"; }

    static Thread* current();

};


class JavaThread;

class Threads {
#ifdef PTHREAD_OKAY
private:
    static std::map<pthread_t, Thread*> _threads_table; /* for current() */
public:
    static Thread* get_pthread_by_id(pthread_t id)  { return _threads_table[id]; }
    static void register_thread(Thread*);
#endif
private:
    static JavaThread* _thread_list; /* the head of the list */
    static int         _number_of_threads;
    static int         _number_of_non_daemon_threads;
    static int         _return_code;
    static int         _thread_claim_parity;
public:
    // Thread management
    // force_daemon is a concession to JNI, where we may need to add a
    // thread to the thread list before allocating its thread object
    static void add(JavaThread* p, bool force_daemon = false);
    static void remove(JavaThread* p);
    static bool includes(JavaThread* p);

    static jint create_vm(JavaVMInitArgs* args, bool* canTryAgain);
    static bool destroy_vm();
};











#endif //MINISPOT_THREAD_H
