//
// Created by GentlyGuitar on 5/23/2017.
//

#include <iostream>
#include <sstream>
#include "ostream.h"
#include "runtime/globals.h"

std::ofstream Loggers::todo;
std::string Loggers::todo_path;

bool Loggers::init() {
    //todo_path = "log/todo.log";
    todo_path = "C:\\Users\\GentlyGuitar\\ClionProjects\\MiniSpot\\Debug\\todo.log";
    todo.open(todo_path, std::ofstream::out);
    if (PrintInitialization) {
        std::cout << "done init loggers" << std::endl;
    }
}


std::vector<std::string> Strings::split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}