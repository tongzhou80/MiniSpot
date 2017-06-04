//
// Created by GentlyGuitar on 6/3/2017.
//

#ifndef MINISPOT_CLASSLOADERDATA_HPP_H
#define MINISPOT_CLASSLOADERDATA_HPP_H

#include <oops/oop.h>

class ClassLoaderData {
    oop _class_loader;
    Metaspace* _metaspace;
public:
    static ClassLoaderData * _the_null_class_loader_data;

};

#endif //MINISPOT_CLASSLOADERDATA_HPP_H
