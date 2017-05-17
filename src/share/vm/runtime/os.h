//
// Created by tzhou on 4/22/17.
//

#ifndef MINISPOT_OS_H
#define MINISPOT_OS_H

#include <sys/types.h>

typedef pthread_t thread_id_t;

class OSThread;
class Thread;


class os {
    // threads
public:
    enum ThreadType {
        vm_thread,
        cgc_thread,        // Concurrent GC thread
        pgc_thread,        // Parallel GC thread
        java_thread,
        compiler_thread,
        watcher_thread,
        sampler_thread,
        os_thread
    };

    static const char * thread_type_str(ThreadType t) {
        switch(t){
            case vm_thread:       return "VMThread";
            case cgc_thread:      return "ConcGCThread";
            case pgc_thread:      return "ParGCThread";
            case java_thread:     return "JavaThread";
            case compiler_thread: return "CompilerThread";
            case watcher_thread:  return "WatcherThread";
            case sampler_thread:  return "SamplerThread";
            default:              return "UnknownThread";
        }
    }

private:
    static OSThread*          _starting_thread;
public:
    static void start_thread(Thread*);
    static bool create_thread(Thread*, ThreadType, int stack_size=0);

    // do not use a system-specific thread id to make cross-platform easier
    static thread_id_t gettid();
//#ifdef __linux__
//public:
//    static pid_t gettid();
//#endif
};

#endif //MINISPOT_OS_H
