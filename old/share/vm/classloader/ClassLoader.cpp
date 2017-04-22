//
// Created by GentlyGuitar on 12/13/2016.
//

#include "ClassLoader.h"
#include "../oops/JClass.h"
#include "../memory/Perm.h"

ClassLoader::ClassLoader() {
    _classparser_ = new ClassParser();
    initClasspaths();
}

ClassLoader::~ClassLoader() {
    delete _classparser_;

    if (PrintDestruction) {
        std::cout << "*** destruct ClassLoader ***" << std::endl;
    }
}

void ClassLoader::initClasspaths() {
    std::string cur_dir = ".";
#ifdef __CYGWIN__
    std::string test_dir = "C:/Users/GentlyGuitar/ClionProjects/Magnolia/src/test/";
#elif __linux__
    //std::string test_dir = "/home/tzhou/ClionProjects/Magnolia/src/test/";
    std::string test_dir = "/home/zhoutong1/Desktop/Magnolia/src/test/";
#endif
    _classpaths_.push_back(cur_dir);
    _classpaths_.push_back(test_dir);
}

void ClassLoader::load(std::string class_name) {
    _classname = class_name;
    _classpath = resolveClassPath(class_name);
    _classfile = _classparser_->parse_from_file(_classpath);
    loadToVM();
}

//bool ClassLoader::isLoaded(std::string) {
//
//}

// parse package
std::string ClassLoader::resolveClassPath(std::string name) {
    return _classpaths_[1] + name;
}

void ClassLoader::loadToVM() {
    _klass = Perm::createJClass(_classfile);

}


void ClassLoader::parseBytecode() {

}