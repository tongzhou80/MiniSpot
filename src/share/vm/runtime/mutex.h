//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_MUTEX_H
#define MINISPOT_MUTEX_H


/* !!! this file should be in linux/ */

#include <pthread.h>
#include <semaphore.h>
#include <utilities/debug.h>

class Monitor {
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
public:
    Monitor()  { int ret = pthread_mutex_init(&_mutex, NULL); guarantee(ret == 0, "Mutex initialize failed"); }
    ~Monitor()  { pthread_mutex_destroy(&_mutex); }
    pthread_mutex_t* mutex()  { return &_mutex; }
    pthread_cond_t* cond()  { return &_cond; }
    void lock()  { pthread_mutex_lock(&_mutex); }
    void unlock()  { pthread_mutex_unlock(&_mutex); }
    void wait()  { pthread_cond_wait(&_cond, &_mutex); }
    void signal()  { pthread_cond_signal(&_cond); }
    void signal_all()  { pthread_cond_broadcast(&_cond); }
};

class Mutex {
    sem_t _sem;
public:
    Mutex() {
        sem_init(&_sem, 0, 0);
    }
    ~Mutex() {
        ~sem_destroy(&_sem);
    }
    void lock() { sem_wait(&_sem); }
    void unlock() { sem_post(&_sem); }
};

/* A HotSpot style MutexLocker */
class MutexLocker {
    Mutex* _mutex;
public:
    MutexLocker(Mutex* m)  {
        _mutex = m;
        _mutex->lock();
    }
    ~MutexLock()  {
        _mutex->unlock();
    }
};


class Locks {
public:
    static Mutex* Heap_lock;
};

#endif //MINISPOT_MUTEX_H
