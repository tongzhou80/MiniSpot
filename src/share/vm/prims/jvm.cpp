//
// Created by GentlyGuitar on 5/26/2017.
//

#include "jvm.h"
#include "jni.h"
#include "classfile/systemDictionary.h"


/* always use app class loader and ignore the loader param for now */
jclass find_class_from_class_loader(Symbol* name, Handle loader) {
    Klass* klass = SystemDictionary::resolve_or_fail(name, loader);
}