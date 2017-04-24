//
// Created by tzhou on 4/23/17.
//

#include "namedThread.h"

// NamedThread --  non-JavaThread subclasses with multiple
// uniquely named instances should derive from this.
NamedThread::NamedThread() : Thread() {
    _name = NULL;
    _processed_thread = NULL;
}

