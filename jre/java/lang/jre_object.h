//
// Created by tzhou on 4/29/17.
//

#ifndef MINISPOT_JRE_OBJECT_H
#define MINISPOT_JRE_OBJECT_H

#include <vector>
#include <string>
#include "prims/jni.h"

struct JREFieldDesc {
    std::string descriptor;
    std::vector<std::string> flags;
};

struct JREClassDesc {

};

class JRE_Object {
public:
    static jboolean equals(JNIEnv *env, jobject obj);
    static jclass getClass(JNIEnv* env, jobject obj);

    /* for internal parsing use */
    static std::vector<JREFieldDesc*> __fields__();
    static std::vector<JREFieldDesc*> __methods__();
};


#endif //MINISPOT_JRE_OBJECT_H
