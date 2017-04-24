cmake_minimum_required(VERSION 3.5)
project(MiniSpot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

set(SOURCE_FILES
        main.cpp
        src/share/vm/prims/jni.cpp src/share/vm/prims/jni.h
        src/share/vm/runtime/threads/osThread.cpp src/share/vm/runtime/threads/osThread.h
        src/share/vm/runtime/threads/thread.cpp src/share/vm/runtime/threads/thread.h
        src/share/vm/utilities/globalDefinitions.cpp src/share/vm/utilities/globalDefinitions.h
        src/share/vm/utilities/debug.cpp src/share/vm/utilities/debug.h
        src/share/vm/runtime/globals.cpp src/share/vm/runtime/globals.h
        src/share/vm/runtime/os.cpp src/share/vm/runtime/os.h
        src/share/vm/runtime/mutex.cpp src/share/vm/runtime/mutex.h src/share/vm/runtime/threads/javaThread.cpp src/share/vm/runtime/threads/javaThread.h src/share/vm/runtime/threads/namedThread.cpp src/share/vm/runtime/threads/namedThread.h)
add_executable(MiniSpot ${SOURCE_FILES})