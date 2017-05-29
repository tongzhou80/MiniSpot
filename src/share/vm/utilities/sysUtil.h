//
// Created by GentlyGuitar on 5/29/2017.
//

#ifndef MINISPOT_SYSUTIL_H
#define MINISPOT_SYSUTIL_H


#include <cstring>

class SysUtil {
public:
    template <typename T>
    static void swapEndianness(T* buf);

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

#endif //MINISPOT_SYSUTIL_H
