//
// Created by zhoutong1 on 12/22/16.
//

#include "JObject.h"
#include "ObjectHeader.h"

JObject::JObject(JClass *klass) {
    _header_->setJclass(klass);
    _body_len = klass->fields_size();
    _body = new u1[_body_len];
}

