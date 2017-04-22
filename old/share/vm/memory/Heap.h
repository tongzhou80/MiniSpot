//
// Created by zhoutong1 on 12/22/16.
//

#ifndef MAGNOLIA_HEAP_H
#define MAGNOLIA_HEAP_H

class JObject;
class JClass;

class Heap {
public:
    static JObject* createJObject(JClass*);
};

#endif //MAGNOLIA_HEAP_H
