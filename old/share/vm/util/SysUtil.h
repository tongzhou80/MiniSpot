//
// Created by GentlyGuitar on 11/5/2016.
//

#ifndef MAGNOLIA_SYSUTIL_H
#define MAGNOLIA_SYSUTIL_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <map>
#include "../global/TypeDef.h"
#include "../interpreter/Bytecode.h"

class SysUtil {
public:
    template <typename T>
    static void swapEndianness(T* buf);

    static std::map<char, JBCMeta*> bcdict;
    static void init_bcdict();
};


template<typename T>
void SysUtil::swapEndianness(T* buf)
{
    T copy;
    std::memcpy(&copy, buf, sizeof(T));
    for (int i = 0; i < sizeof(T); i++) {
        std::memcpy((char*)buf+i, (char*)&copy+(sizeof(T)-1-i), 1);
    }
}

#endif //MAGNOLIA_SYSUTIL_H
