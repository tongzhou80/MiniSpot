cmake_minimum_required(VERSION 3.5)
project(MiniSpot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

set(SOURCE_FILES
        main.cpp
        src/share/vm/prims/jni.cpp src/share/vm/prims/jni.h
        src/share/vm/runtime/osThread.cpp src/share/vm/runtime/osThread.h
        src/share/vm/runtime/thread.cpp src/share/vm/runtime/thread.h
        src/share/vm/utilities/globalDefinitions.cpp src/share/vm/utilities/globalDefinitions.h
        src/share/vm/utilities/debug.cpp src/share/vm/utilities/debug.h
        src/share/vm/runtime/globals.cpp src/share/vm/runtime/globals.h
        src/share/vm/runtime/os.cpp src/share/vm/runtime/os.h
        src/share/vm/runtime/mutex.cpp src/share/vm/runtime/mutex.h)
add_executable(MiniSpot ${SOURCE_FILES})