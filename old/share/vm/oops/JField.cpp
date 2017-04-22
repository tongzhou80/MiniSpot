//
// Created by zhoutong1 on 12/25/16.
//

#include "JField.h"

JField::JField(ClassFileFieldInfo *finfo, JClass* klass) {
    /* access flag */

    /* name */
    _name = klass->constantPool()->getUtf8(finfo->name_index);

    /* descriptor*/
    std::string desc = klass->constantPool()->getUtf8(finfo->descriptor_index);
    if (desc == "I") {
        _type = JField::INT;
        _real_size = 4;
        _heap_size = 4;
    }
    else if (desc == "Z") {
        _type = JField::BOOLEAN;
        _real_size = 1;
        _heap_size = 4;
    }
    else if (desc == "J") {
        _type = JField::LONG;
        _real_size = 8;
        _heap_size = 8;
    }
}
