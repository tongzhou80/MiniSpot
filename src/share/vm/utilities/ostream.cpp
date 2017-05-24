//
// Created by GentlyGuitar on 5/23/2017.
//

#include <iostream>
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