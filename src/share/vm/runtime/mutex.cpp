//
// Created by tzhou on 4/23/17.
//

#include "mutex.h"

//
//void Monitor::wait(bool predicate) {
//    pthread_mutex_lock(&_mutex);
//    while (!predicate) {
//        pthread_cond_wait(&_cond, &_mutex);
//    }
//    pthread_mutex_unlock(&_mutex);
//}
//
//void Monitor::signal() {
//
//}