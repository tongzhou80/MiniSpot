//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_MUTEX_H
#define MINISPOT_MUTEX_H


/* !!! this file should be in linux/ */

#include <pthread.h>

class Monitor {
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
public:
    pthread_mutex_t* mutex()  { return &_mutex; }
    pthread_cond_t* cond()  { return &_cond; }

//    void wait(bool predicate);
//    void signal();
//    void signal_all();
};

#endif //MINISPOT_MUTEX_H
