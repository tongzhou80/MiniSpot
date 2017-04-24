//
// Created by tzhou on 4/23/17.
//

#ifndef MINISPOT_NAMEDTHREAD_H
#define MINISPOT_NAMEDTHREAD_H

#include <cstring>
#include "namedThread.h"

class Thread;
class JavaThread;


// Name support for threads.  non-JavaThread subclasses with multiple
// uniquely named instances should derive from this.
class NamedThread: public Thread {
    friend class VMStructs;
    enum {
        max_name_len = 64
    };
private:
    char* _name;
    // log JavaThread being processed by oops_do
    JavaThread* _processed_thread;

public:
    NamedThread();
    ~NamedThread();
    // May only be called once per thread.
    //void set_name(const char* format, ...)  ATTRIBUTE_PRINTF(2, 3);
    void initialize_named_thread();
    virtual bool is_Named_thread() const { return true; }
    virtual char* name() const { return _name == NULL ? (char*)"Unknown Thread" : _name; }
    JavaThread *processed_thread() { return _processed_thread; }
    void set_processed_thread(JavaThread *thread) { _processed_thread = thread; }

};



#endif //MINISPOT_NAMEDTHREAD_H
