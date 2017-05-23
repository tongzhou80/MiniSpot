//
// Created by tzhou on 11/4/16.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <assert.h>
#include "ClassFile.h"



ClassFile* ClassFileParser::parse() {
    _reader.open(_class_path, std::ifstream::binary);
    if (!_reader) {
        std::cerr << "open class file: \"" << _class_path << "\" failed" << std::endl;
        exit(0);
    }

    _classfile = new ClassFile();

    /* =========================== notice ========================= */
    /* 1. Class files are big endian */
    /* 2. Do not change the call order to the following functions
     * that read and parse class file */

    /* read and verify magic number */
    if (!parse_magic()) {
        std::cerr << "bad magic number, exit." << std::endl;
        exit(0);
    }

    /* read minor and major version. Verify major version number */
    if (!parse_version()) {
        std::cerr << "bad major version number, exit." << std::endl;
        exit(0);
    }

    /* parse constant pool */
    if (!parse_constant_pool()) {
        std::cerr << "bad constant pool, exit." << std::endl;
        exit(0);
    }

    /* parse access flags */
    if (!parse_class_access_flags()) {
        std::cerr << "bad access flag, exit." << std::endl;
        exit(0);
    }

    if (!parse_this_and_super_class()) {
        std::cerr << "bad this class or super class field, exit." << std::endl;
        exit(0);
    }

    if (!parse_interfaces()) {
        std::cerr << "bad interface, parsing failed, exit." << std::endl;
        exit(0);
    }

    if (!parse_fields()) {
        std::cerr << "parsing fields failed, exit." << std::endl;
        exit(0);
    }

    if (!parse_methods()) {
        std::cerr << "parsing methods failed, exit." << std::endl;
        exit(0);
    }

}

ClassFileParser::ClassFileParser() {

}

ClassFileParser::ClassFileParser(std::string file_path) {
    _class_path = file_path;
}

ClassFileParser::~ClassFileParser() {
    _reader.close();
    delete _classfile;

    if (PrintDestruction) {
        std::cout << "*** destruct ClassFileParser ***" << std::endl;
    }
}

ClassFile* ClassFileParser::parse_from_file(std::string file_path) {
    _class_path = file_path;
    parse();
    return _classfile;
}

bool ClassFileParser::parse_magic() {
    _reader.read((char*)&(_classfile->magic), sizeof(_classfile->magic));
    int32_t cafebabe = 0xBEBAFECA;

    if (!(_classfile->magic ^ cafebabe)) {
        return true;
    }
    else {
        return false;
    }
}

bool ClassFileParser::parse_version() {
    _reader.read((char*)&(_classfile->minor_version), sizeof(_classfile->minor_version));
    _reader.read((char*)&(_classfile->major_version), sizeof(_classfile->major_version));

    /* Use big endian directly for performance */
    switch (_classfile->major_version) {
        case 0x2e00:
            _classfile->java_version = 1.2;
            break;
        case 0x2f00:
            _classfile->java_version = 1.3;
            break;
        case 0x3000:
            _classfile->java_version = 1.4;
            break;
        case 0x3100:
            _classfile->java_version = 5;
            break;
        case 0x3200:
            _classfile->java_version = 6;
            break;
        case 0x3300:
            _classfile->java_version = 7;
            break;
        case 0x3400: // should be 52 in decimal
            _classfile->java_version = 8;
            break;
        default:
            return false;
    }
    SysUtil::swapEndianness(&_classfile->minor_version);
    SysUtil::swapEndianness(&_classfile->major_version);

    return true;
}

/* todo: some printings need change */
bool ClassFileParser::parse_constant_pool() {
    u2 cpc;
    _reader.read((char*)&cpc, sizeof(u2));
    SysUtil::swapEndianness(&cpc);
    _classfile->constant_pool_count = cpc;
    _classfile->constant_pool = new CpInfo*[cpc+1]; /* pool index starts from 1 */
    for(int i = 1; i < cpc; i++) {
        u1 tag;
        _reader.read((char*)&tag, sizeof(u1));
        switch (tag) {
            case 1: {
                ConstantUtf8Info* info = new ConstantUtf8Info();
                info->tag = tag;
                _reader.read((char*)&info->length, sizeof(info->length));
                SysUtil::swapEndianness(&info->length);
                char* buf = new char[info->length+1];
                _reader.read(buf, info->length);
                buf[info->length] = 0;
                info->bytes = (u1*)buf;
                _classfile->constant_pool[i] = info;

                if (PrintConstantPool) {
                    char const_type[100];
                    std::sprintf(const_type, "#%d = Uft8", i);
                    std::cout << std::left << std::setw(30) << const_type << buf << std::endl;
                }
                break;
            }
            case 3: {
                if (PrintConstantPool) {
                    std::cout << "#" << i << " = Integer" << std::endl;
                }
                ConstantIntegerInfo* info = new ConstantIntegerInfo();
                info->tag = tag;
                _reader.read((char*)&info->bytes, sizeof(info->bytes));
                SysUtil::swapEndianness(&info->bytes);
                _classfile->constant_pool[i] = info;
                break;
            }
            case 4: {
                if (PrintConstantPool) {
                    std::cout << "#" << i << " = Float" << std::endl;
                }
                ConstantFloatInfo* info = new ConstantFloatInfo();
                info->tag = tag;
                _reader.read((char*)&info->bytes, sizeof(info->bytes));
                SysUtil::swapEndianness(&info->bytes);
                _classfile->constant_pool[i] = info;
                break;
            }
            case 5: {
                if (PrintConstantPool) {
                    std::cout << "#" << i << " = Long" << std::endl;
                }
                ConstantLongInfo* info = new ConstantLongInfo();
                info->tag = tag;
                _reader.read((char*)&info->high_bytes, sizeof(info->high_bytes));
                _reader.read((char*)&info->low_bytes, sizeof(info->low_bytes));
                SysUtil::swapEndianness(&info->high_bytes);
                SysUtil::swapEndianness(&info->low_bytes);
                _classfile->constant_pool[i] = info;
                break;
            }
            case 7: {
                ConstantClassInfo* info = new ConstantClassInfo();
                info->tag = tag;
                _reader.read((char*)&info->name_index, sizeof(info->name_index));
                SysUtil::swapEndianness(&info->name_index);
                _classfile->constant_pool[i] = info;

                if (PrintConstantPool) {
                    char const_type[100];
                    std::sprintf(const_type, "#%d = ConstantClassInfo", i);
                    std::cout << std::left << std::setw(30) << const_type
                    << "#" << info->name_index << std::endl;
                }
                break;
            }
            case 8: {
                ConstantStringInfo* info = new ConstantStringInfo();
                info->tag = tag;
                _reader.read((char*)&info->string_index, sizeof(info->string_index));
                SysUtil::swapEndianness(&info->string_index);
                _classfile->constant_pool[i] = info;

                if (PrintConstantPool) {
                    char const_type[100];
                    std::sprintf(const_type, "#%d = String", i);
                    std::cout << std::left << std::setw(30) << const_type
                    << "#" << info->string_index << std::endl;
                }
                break;
            }
            case 9: {
                ConstantFieldrefInfo* info = new ConstantFieldrefInfo();
                info->tag = tag;
                _reader.read((char*)&info->class_index, sizeof(info->class_index));
                _reader.read((char*)&info->name_and_type_index, sizeof(info->name_and_type_index));
                SysUtil::swapEndianness(&info->class_index);
                SysUtil::swapEndianness(&info->name_and_type_index);
                _classfile->constant_pool[i] = info;

                if (PrintConstantPool) {
                    char const_type[100];
                    std::sprintf(const_type, "#%d = Fieldref", i);
                    std::cout << std::left << std::setw(30) << const_type
                    << "#" << info->class_index << ".#" << info->name_and_type_index << std::endl;
                }
                break;
            }
            case 10: {
                ConstantMethodrefInfo* info = new ConstantMethodrefInfo();
                info->tag = tag;
                _reader.read((char*)&info->class_index, sizeof(info->class_index));
                _reader.read((char*)&info->name_and_type_index, sizeof(info->name_and_type_index));
                SysUtil::swapEndianness(&info->class_index);
                SysUtil::swapEndianness(&info->name_and_type_index);
                _classfile->constant_pool[i] = info;

                if (PrintConstantPool) {
                    char const_type[100];
                    std::sprintf(const_type, "#%d = Methodref", i);
                    std::cout << std::left << std::setw(30) << const_type
                    << "#" << info->class_index << ".#" << info->name_and_type_index << std::endl;
                }
                break;
            }
            case 11: {
                if (PrintConstantPool) {
                    std::cout << "#" << i << " = InterfaceMethodref" << std::endl;
                }
                ConstantInterfaceMethodrefInfo* info = new ConstantInterfaceMethodrefInfo();
                info->tag = tag;
                _reader.read((char*)&info->class_index, sizeof(info->class_index));
                _reader.read((char*)&info->name_and_type_index, sizeof(info->name_and_type_index));
                SysUtil::swapEndianness(&info->class_index);
                SysUtil::swapEndianness(&info->name_and_type_index);
                _classfile->constant_pool[i] = info;
                break;
            }
            case 12: {
                ConstantNameAndTypeInfo* info = new ConstantNameAndTypeInfo();
                info->tag = tag;
                _reader.read((char*)&info->name_index, sizeof(info->name_index));
                _reader.read((char*)&info->descriptor_index, sizeof(info->descriptor_index));
                SysUtil::swapEndianness(&info->name_index);
                SysUtil::swapEndianness(&info->descriptor_index);
                _classfile->constant_pool[i] = info;

                if (PrintConstantPool) {
                    char const_type[100];
                    std::sprintf(const_type, "#%d = NameAndType", i);
                    std::cout << std::left << std::setw(30) << const_type
                    << "#" << info->name_index << ".#" << info->descriptor_index << std::endl;
                }
                break;
            }
            case 15: {
                if (PrintConstantPool) {
                    std::cout << "#" << i << " = MethodHandle" << std::endl;
                }
                ConstantMethodHandleInfo* info = new ConstantMethodHandleInfo();
                info->tag = tag;
                _reader.read((char*)&info->reference_kind, sizeof(info->reference_kind));
                _reader.read((char*)&info->reference_index, sizeof(info->reference_index));
                SysUtil::swapEndianness(&info->reference_kind);
                SysUtil::swapEndianness(&info->reference_index);
                _classfile->constant_pool[i] = info;
                break;
            }
            case 16: {
                if (PrintConstantPool) {
                    std::cout << "#" << i << " = MethodType" << std::endl;
                }
                ConstantMethodTypeInfo* info = new ConstantMethodTypeInfo();
                info->tag = tag;
                _reader.read((char*)&info->descriptor_index, sizeof(info->descriptor_index));
                SysUtil::swapEndianness(&info->descriptor_index);
                _classfile->constant_pool[i] = info;
                break;
            }
            case 18: {
                if (PrintConstantPool) {
                    std::cout << "#" << i << " = InvokeDynamic" << std::endl;
                }
                ConstantInvokeDynamicInfo* info = new ConstantInvokeDynamicInfo();
                info->tag = tag;
                _reader.read((char*)&info->bootstrap_method_attr_index, sizeof(info->bootstrap_method_attr_index));
                _reader.read((char*)&info->name_and_type_index, sizeof(info->name_and_type_index));
                SysUtil::swapEndianness(&info->bootstrap_method_attr_index);
                SysUtil::swapEndianness(&info->bootstrap_method_attr_index);
                _classfile->constant_pool[i] = info;
                break;
            }
            default:
                std::cerr << "unknown constant type " << tag << std::endl;
                return false;
        }
    }
    ConstantPool* pool = new ConstantPool(_classfile->constant_pool, _classfile->constant_pool_count);
    _classfile->cp_arr = pool;
    _cp = pool;
    return true;
}

bool ClassFileParser::parse_class_access_flags() {
    _reader.read((char*)&_classfile->access_flags, sizeof(_classfile->access_flags));
    SysUtil::swapEndianness(&_classfile->access_flags);

    /* todo: to be completed */
    switch (_classfile->access_flags & 0x000f) {
        case 0x0001:
            _classfile->acc_public = true;
            break;
        default:
            return false;
    }

    switch (_classfile->access_flags & 0x00f0) {
        case 0x0010:
            _classfile->acc_final = true;
            break;
        case 0x0020:
            _classfile->acc_super = true;
            break;
        default:
            return false;
    }

    /* todo: to be completed */
    if (PrintDisassembled) {
        std::cout << "class access flags: ";
        std::cout << std::endl;
    }

    return true;
}

bool ClassFileParser::parse_method_access_flags(ClassFileMethodInfo* minfo) {
    /* todo: to set all flags false first */
    minfo->acc_public = false;
    minfo->acc_private = false;
    minfo->acc_protected = false;
    minfo->acc_static = false;
    minfo->acc_final = false;
    minfo->acc_final = false;
    minfo->acc_synchronized = false;
    minfo->acc_bridge = false;
    minfo->acc_varargs = false;
    minfo->acc_native = false;
    minfo->acc_abstract = false;
    minfo->acc_strict = false;
    minfo->acc_synthetic = false;

    minfo->access_flags = 0x1111;


    /* todo: to be completed */
    int check_set = 0;
    u1 b3 = minfo->access_flags & 0x000f;
    if ((b3 & 0x01) != 0) {
        minfo->acc_public = true;
        check_set++;
    }

    if ((b3 & 0x02) != 0) {
        minfo->acc_private = true;
        check_set++;
    }

    if ((b3 & 0x04) != 0) {
        minfo->acc_protected = true;
        check_set++;
    }

    if ((b3 & 0x08) != 0) {
        minfo->acc_static = true;
        check_set++;
    }

    /* check 1: each method of a class may have at most one of its
     * ACC_PUBLIC, ACC_PRIVATE, and ACC_PROTECTED flags set */
    if (check_set > 1) {
        std::cerr << "parsing error, each method of a class may have at most one of its "
                             "ACC_PUBLIC, ACC_PRIVATE, and ACC_PROTECTED flags set" << std::endl;
    }

    u1 b2 = (minfo->access_flags & 0x00f0) >> 4;
    if ((b2 & 0x01) != 0) {
        minfo->acc_final = true;

    }

    if ((b2 & 0x02) != 0) {
        minfo->acc_synchronized = true;

    }

    if ((b2 & 0x04) != 0) {
        minfo->acc_bridge = true;

    }

    if ((b2 & 0x08) != 0) {
        minfo->acc_varargs = true;

    }

    u1 b1 = (minfo->access_flags & 0x0f00) >> 8;
    if ((b1 & 0x01) != 0) {
        minfo->acc_native = true;

    }


    if ((b1 & 0x04) != 0) {
        minfo->acc_abstract = true;

    }

    if ((b1 & 0x08) != 0) {
        minfo->acc_strict = true;

    }

    u1 b0 = (minfo->access_flags & 0xf000) >> 12;
    if ((b0 & 0x01) != 0) {
        minfo->acc_synthetic = true;

    }


    /* todo: all sorts of access flag check */

    /* todo: to be completed */
    if (PrintDisassembled) {
        std::cout << "method access flags: ";
        std::cout << std::endl;
    }

    return true;
}

bool ClassFileParser::parse_this_and_super_class() {
    _reader.read((char*)&_classfile->this_class, sizeof(_classfile->this_class));
    _reader.read((char*)&_classfile->super_class, sizeof(_classfile->super_class));
    SysUtil::swapEndianness(&_classfile->this_class);
    SysUtil::swapEndianness(&_classfile->super_class);
    return true;
}

bool ClassFileParser::parse_interfaces() {
    _reader.read((char*)&_classfile->interfaces_count, sizeof(_classfile->interfaces_count));
    SysUtil::swapEndianness(&_classfile->interfaces_count);

    if (_classfile->interfaces_count != 0) {
        u2* buf = new u2[_classfile->interfaces_count];
        _reader.read((char*)buf, _classfile->interfaces_count);
        _classfile->interfaces = buf;
    }
    else {
        _classfile->interfaces = NULL;
    }

    if (PrintDisassembled) {
        if (_classfile->interfaces_count != 0) {
            std::cout << "interfaces: ";
            for (int i = 0; i < _classfile->interfaces_count; i++) {
                std::cout << "#" << _classfile->interfaces[i] << " ";
            }
            std::cout << std::endl;
        }
    }
    return true;
}

bool ClassFileParser::parse_fields() {
    _reader.read((char*)&_classfile->fields_count, sizeof(_classfile->fields_count));
    SysUtil::swapEndianness(&_classfile->fields_count);
    _classfile->fields = new ClassFileFieldInfo*[_classfile->fields_count];

    for (int i = 0; i < _classfile->fields_count; i++) {
        ClassFileFieldInfo* finfo = new ClassFileFieldInfo();
        _reader.read((char*)&finfo->access_flags, sizeof(finfo->access_flags));
        _reader.read((char*)&finfo->name_index, sizeof(finfo->name_index));
        _reader.read((char*)&finfo->descriptor_index, sizeof(finfo->descriptor_index));
        _reader.read((char*)&finfo->attributes_count, sizeof(finfo->attributes_count));
        SysUtil::swapEndianness(&finfo->access_flags);
        SysUtil::swapEndianness(&finfo->name_index);
        SysUtil::swapEndianness(&finfo->descriptor_index);
        SysUtil::swapEndianness(&finfo->attributes_count);
        if (finfo->attributes_count != 0) {
            //finfo->attributes = parse_field_attr_info(finfo->attributes_count);
            finfo->attributes = get_attr_array(finfo->attributes_count);
        }
        else {
            finfo->attributes = NULL;
        }
        _classfile->fields[i] = finfo;
    }

    if (PrintDisassembled) {
        /* todo: only print fields name for now */
        std::cout << "fields: " << std::endl;
        for (int i = 0; i < _classfile->fields_count; i++) {
            int name_i = _classfile->fields[i]->name_index;
            int desc_i = _classfile->fields[i]->descriptor_index;
            int attr_cnt = _classfile->fields[i]->attributes_count;
            ConstantUtf8Info* name = (ConstantUtf8Info*)_cp->get(name_i, ConstantPool::ConstantUtf8);
            ConstantUtf8Info* desc = (ConstantUtf8Info*)_cp->get(desc_i, ConstantPool::ConstantUtf8);
            //ConstantUtf8Info* u_info = get_utf8_constant(f_i);
            std::cout << "  name: " << name->bytes << std::endl;
            std::cout << "  descriptor: " << desc->bytes << std::endl;
            std::cout << "  attr num: " << attr_cnt << std::endl;
        }
    }
    return true;
}



ClassFileAttributeInfo** ClassFileParser::get_attr_array(int count) {
    ClassFileAttributeInfo** attr_arr = new ClassFileAttributeInfo*[count];
    for (int i = 0; i < count; i++) {
        ClassFileAttributeInfo* attr = new ClassFileAttributeInfo();
        _reader.read((char*)&attr->attribute_name_index, sizeof(attr->attribute_name_index));
        SysUtil::swapEndianness(&attr->attribute_name_index);
        _reader.read((char*)&attr->attribute_length, sizeof(attr->attribute_length));
        SysUtil::swapEndianness(&attr->attribute_length);
        char* buf = new char[attr->attribute_length+1];
        _reader.read(buf, attr->attribute_length);
        attr->info = (u1*)buf;
        attr_arr[i] = attr;
    }
    return attr_arr;
}

ClassFileCodeAttribute* ClassFileParser::parse_code_attribute(ClassFileAttributeInfo *attr) {
    ClassFileCodeAttribute* code = new ClassFileCodeAttribute();
    code->attribute_name_index = attr->attribute_name_index;
    code->attribute_length = attr->attribute_length;
    size_t pos = 0;
    size_t read_len = sizeof(code->max_stack);
    std::memcpy(&code->max_stack, (char*)&attr->info[0]+pos, read_len);
    SysUtil::swapEndianness(&code->max_stack);

    pos += read_len;
    read_len = sizeof(code->max_locals);
    std::memcpy(&code->max_locals, (char*)&attr->info[0]+pos, read_len);
    SysUtil::swapEndianness(&code->max_locals);

    pos += read_len;
    read_len = sizeof(code->code_length);
    std::memcpy(&code->code_length, (char*)&attr->info[0]+pos, read_len);
    SysUtil::swapEndianness(&code->code_length);

    pos += read_len;
    read_len = code->code_length;
    code->code = new u1[read_len+1];
    code->code[read_len] = 0;
    std::memcpy(code->code, (char*)&attr->info[0]+pos, read_len);

    pos += read_len;
    read_len = sizeof(code->exception_table_length);
    std::memcpy(&code->exception_table_length, (char*)&attr->info[0]+pos, read_len);


    return code;
}

bool ClassFileParser::parse_method_attributes(ClassFileMethodInfo* m) {
    if (ClassParsingVerbose) {
        std::cout << "method attribute count: " << m->attributes_count << std::endl;
    }

    for (int i = 0; i < m->attributes_count; i++) {
        ClassFileAttributeInfo* attr = m->attributes[i];
        ConstantUtf8Info* utf_info = (ConstantUtf8Info*)_cp->get(attr->attribute_name_index, ConstantPool::ConstantUtf8);
        if (ClassParsingVerbose) {
            std::cout << "atrr name: " << (char*)utf_info->bytes << std::endl;
        }
        if (strcmp((char*)utf_info->bytes, "Code") == 0) {
            m->code = parse_code_attribute(attr);
        }
    }
}


bool ClassFileParser::parse_methods() {
    _reader.read((char*)&_classfile->methods_count, sizeof(_classfile->methods_count));
    SysUtil::swapEndianness(&_classfile->methods_count);
    _classfile->methods = new ClassFileMethodInfo*[_classfile->methods_count];

    for (int i = 0; i < _classfile->methods_count; i++) {
        ClassFileMethodInfo* minfo = new ClassFileMethodInfo();
        _reader.read((char*)&minfo->access_flags, sizeof(minfo->access_flags));
        _reader.read((char*)&minfo->name_index, sizeof(minfo->name_index));
        _reader.read((char*)&minfo->descriptor_index, sizeof(minfo->descriptor_index));
        _reader.read((char*)&minfo->attributes_count, sizeof(minfo->attributes_count));
        SysUtil::swapEndianness(&minfo->access_flags);
        SysUtil::swapEndianness(&minfo->name_index);
        SysUtil::swapEndianness(&minfo->descriptor_index);
        SysUtil::swapEndianness(&minfo->attributes_count);

        parse_method_access_flags(minfo);
        if (minfo->attributes_count != 0) {
            //minfo->attributes = parse_field_attr_info(minfo->attributes_count);
            minfo->attributes = get_attr_array(minfo->attributes_count);
        }
        else {
            minfo->attributes = NULL;
        }
        parse_method_attributes(minfo);
        _classfile->methods[i] = minfo;
    }

    if (PrintDisassembled) {
        /* todo: only print methods name for now */
        std::cout << "methods: " << std::endl;
        for (int i = 0; i < _classfile->methods_count; i++) {
            int name_i = _classfile->methods[i]->name_index;
            int desc_i = _classfile->methods[i]->descriptor_index;
            ConstantUtf8Info* name = (ConstantUtf8Info*)_cp->get(name_i, ConstantPool::ConstantUtf8);
            ConstantUtf8Info* desc = (ConstantUtf8Info*)_cp->get(desc_i, ConstantPool::ConstantUtf8);
            std::cout << name->bytes << " " << desc->bytes << std::endl;
        }
    }
    return true;
}

std::vector<Bytecode*> ClassFileParser::parseBytecode(u1 * code, int len) {
    std::vector<Bytecode*> bytecodes;
    int p = 0;
    while (p < len) {
        char opcode;
        std::memcpy(&opcode, code+p, sizeof(char));
        p += sizeof(char);
        JBCMeta* meta = SysUtil::bcdict[opcode];
        Bytecode* newbc = new Bytecode(meta);
        newbc->set_args_(code);

        p += meta->arg_len;

        bytecodes.push_back(newbc);
        std::cout << "parsed " << meta->name << std::endl;
        if (meta->name == "invokespecial")
            break;
    }
    return bytecodes;
}

CpInfo* ConstantPool::get(u4 index, ConstantType type) {
    CpInfo* con = pool_array[index];
    assert(con->tag == type);
    return con;
}

std::string ConstantPool::getClassname(u4 index) {
    CpInfo* classconst = pool_array[index];
    assert(classconst->tag == ConstantPool::ConstantClass);
    int nameindex = ((ConstantClassInfo*)classconst)->name_index;
    return getUtf8(nameindex);
}

std::string ConstantPool::getUtf8(u4 index) {
    CpInfo* con = pool_array[index];
    assert(con->tag == ConstantPool::ConstantUtf8);
    ConstantUtf8Info* info = ((ConstantUtf8Info*)con);

    return std::string(((char*)info->bytes), info->length);
}

/* pool_array is owned by/copied from ClassFile and should be deleted by ClassFile
 * instead of here.
 * Otherwise there will be double free.
 */
ConstantPool::~ConstantPool() {
    /* Nothing needs to be freed here */
    if (PrintDestruction) {
        std::cout << "*** destruct ConstantPool ***" << std::endl;
    }
}

ClassFile::~ClassFile() {
    for (int i = 0; i < constant_pool_count; i++) {
        delete constant_pool[i];
    }

    for (int i = 0; i < fields_count; i++) {
        delete fields[i];
    }

    for (int i = 0; i < methods_count; i++) {
        delete methods[i];
    }

    delete cp_arr;

    if (PrintDestruction) {
        std::cout << "*** destruct ClassFile ***" << std::endl;
    }
}