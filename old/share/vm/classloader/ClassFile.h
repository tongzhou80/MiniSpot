//
// Created by tzhou on 11/4/16.
//

#ifndef MAGNOLIA_CLASSFILE_H
#define MAGNOLIA_CLASSFILE_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include "../global/TypeDef.h"
#include "../global/GlobalFlags.h"


//#######################################################################
/* Because these classes directly represent class files, they are used
 * like C structs, thus most members are public
 */


/* classes needing destructors and implemented */
class ClassFile;
class ConstantPool;
class ClassParser;
class ConstantUtf8Info;
class ClassFileAttributeInfo;
class ClassFileCodeAttribute;
class ClassFileMethodInfo;
class ClassFileFieldInfo;

class Bytecode;

class CpInfo {
public:
    u1 tag;

    virtual ~CpInfo() {}
};

/* tag value 1 */
class ConstantUtf8Info: public CpInfo {
public:
    u2 length;
    u1* bytes;

    ~ConstantUtf8Info() {
        delete[] bytes;
        if (PrintDestruction) {
            std::cout << "*** destruct ConstantUtf8Info ***" << std::endl;
        }
    }
    //u1 bytes[length];
};

/* tag value 3 */
class ConstantIntegerInfo: public CpInfo {
public:
    u4 bytes;
};

/* tag value 4 */
class ConstantFloatInfo: public CpInfo {
public:
    u4 bytes;
};

/* tag value 5 */
class ConstantLongInfo: public CpInfo {
public:
    u4 high_bytes;
    u4 low_bytes;
};

/* tag value 6 */
class ConstantDoubleInfo: public CpInfo {
public:
    u4 high_bytes;
    u4 low_bytes;
};

/* tag value 7 */
class ConstantClassInfo: public CpInfo {
public:
    u2 name_index;
};

/* tag value 8 */
class ConstantStringInfo: public CpInfo {
public:
    u2 string_index;
};

/* tag value 9 */
class ConstantFieldrefInfo: public CpInfo {
public:
    u2 class_index;
    u2 name_and_type_index;
};

/* tag value 10 */
class ConstantMethodrefInfo: public CpInfo {
public:
    u2 class_index;
    u2 name_and_type_index;
};

/* tag value 11 */
class ConstantInterfaceMethodrefInfo: public CpInfo {
public:
    u2 class_index;
    u2 name_and_type_index;
};

/* tag value 12 */
class ConstantNameAndTypeInfo: public CpInfo {
public:
    u2 name_index;
    u2 descriptor_index;
};

/* tag value 15 */
class ConstantMethodHandleInfo: public CpInfo {
public:
    u1 reference_kind;
    u2 reference_index;
};

/* tag value 16 */
class ConstantMethodTypeInfo: public CpInfo {
public:
    u2 descriptor_index;
};

/* tag value 18 */
class ConstantInvokeDynamicInfo: public CpInfo {
public:
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
};


class ClassFileAttributeInfo {
public:
    u2 attribute_name_index;
    u4 attribute_length;
    u1* info;

    ~ClassFileAttributeInfo() {
        delete[] info;
        if (PrintDestruction) {
            std::cout << "*** destruct ClassFileAttributeInfo ***" << std::endl;
        }
    }
};

class ExceptionTable {
public:
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

class ClassFileCodeAttribute {
public:
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1* code;
    u2 exception_table_length;
    ExceptionTable** exception_table;
    u2 attributes_count;
    ClassFileAttributeInfo** attributes;

    ~ClassFileCodeAttribute() {
        delete[] code;

        for (int i = 0; i < exception_table_length; i++) {
            delete exception_table[i];
        }

        for (int i = 0; i < attributes_count; i++) {
            delete attributes[i];
        }

        if (PrintDestruction) {
            std::cout << "*** destruct ClassFileCodeAttribute ***" << std::endl;
        }
    }
};

class ClassFileFieldInfo {
public:
    ClassFileFieldInfo() {
        acc_public = false;
        acc_private = false;
        /* todo: to be completed */
    };
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    ClassFileAttributeInfo** attributes;

    ~ClassFileFieldInfo() {
        for (int i = 0; i < attributes_count; i++) {
            delete attributes[i];
        }

        if (PrintDestruction) {
            std::cout << "*** destruct ClassFileFieldAttribute ***" << std::endl;
        }
    }

    //augmented fields and methods
    bool acc_public;
    bool acc_private;
    bool acc_protected;
    bool acc_static;
    bool acc_final;
    bool acc_volatile;

};

class ClassFileMethodInfo {

public:
    ClassFileMethodInfo() {
        acc_public = false;
        acc_private = false;
        /* todo: to be completed */
    };
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    ClassFileAttributeInfo** attributes;

    /* predefined attributes */
    ClassFileCodeAttribute* code;

    ~ClassFileMethodInfo() {
        for (int i = 0; i < attributes_count; i++) {
            delete attributes[i];
        }

        delete code;

        if (PrintDestruction) {
            std::cout << "*** destruct ClassFileMethodInfo ***" << std::endl;
        }
    }

    /* augmented fields and methods */
    bool acc_public;
    bool acc_private;
    bool acc_protected;
    bool acc_static;
    bool acc_final;
    bool acc_synchronized;
    bool acc_bridge;
    bool acc_varargs;
    bool acc_native;
    bool acc_abstract;
    bool acc_strict;
    bool acc_synthetic;

};


class ClassFile {
public:
    ~ClassFile();
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    CpInfo** constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2* interfaces; // index into constant pool
    u2 fields_count;
    ClassFileFieldInfo ** fields;
    u2 methods_count;
    ClassFileMethodInfo** methods;
//    u2 attributes_count;
//    attribute_info attributes[attributes_count];

    float java_version;
    ConstantPool* cp_arr;
    bool acc_public;
    bool acc_final;
    bool acc_super;
    bool acc_interface;
    bool acc_abstract;
    bool acc_synthetic;
    bool acc_annotation;
    bool acc_enum;


};

class ConstantPool {
    //u1* raw_bytes;
    CpInfo** pool_array;
    u2 count;
public:
    enum ConstantType {
        ConstantUtf8 = 1,
        ConstantInteger = 3,
        ConstantClass = 7,
        ConstantMethodRef = 10,
        ConstantInterfaceMethodRef = 11,
        ConstantNameAndType = 12,
    };

    ConstantPool(CpInfo** arr, u2 count) { pool_array = arr; this->count = count; }
    ~ConstantPool();

    void init(CpInfo** arr, u2 count) { pool_array = arr; this->count = count; }
    CpInfo* get(u4 index, ConstantType type);
    std::string getClassname(u4 index);
    std::string getUtf8(u4 index);
};

class ClassParser {
    std::string _class_path;
    ClassFile* _classfile;
    ConstantPool* _cp; // alias to classfile->cp_arr
    std::ifstream _reader;

public:
    static std::vector<Bytecode*> parseBytecode(u1*, int);
    ClassParser();
    ~ClassParser();
    ClassParser(std::string file_path);

    ClassFile* parse_from_file(std::string file_path);
    ClassFile* parse();

    bool parse_magic();
    bool parse_version();
    bool parse_constant_pool();
    bool parse_class_access_flags();

    bool parse_this_and_super_class();
    bool parse_interfaces();
    bool parse_fields();
    bool parse_methods();
    bool parse_method_access_flags(ClassFileMethodInfo* m);

    bool parse_class_from_file(std::string file_path);
    bool parse_method_attributes(ClassFileMethodInfo* m);
    //bool get_constant_by_index(u2 index);
    ConstantUtf8Info* get_utf8_constant(u2 index);

    ClassFileCodeAttribute* parse_code_attribute(ClassFileAttributeInfo *attr);

    ClassFileAttributeInfo **get_attr_array(int count);
};

#endif //MAGNOLIA_CLASSFILE_H

