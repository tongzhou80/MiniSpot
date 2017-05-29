//
// Created by GentlyGuitar on 5/26/2017.
//

#ifndef MINISPOT_JVM_H
#define MINISPOT_JVM_H

#include <runtime/symbol.h>
#include <runtime/handles.h>
#include "jni.h"

jclass find_class_from_class_loader(Symbol& name, Handle loader);


#endif //MINISPOT_JVM_H
