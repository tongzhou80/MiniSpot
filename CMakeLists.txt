cmake_minimum_required(VERSION 3.5)
project(MiniSpot)

include_directories(src/share/vm)
SET(GCC_COMPILE_FLAGS "-std=c++11 -lpthread -g -rdynamic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

set(SOURCE_FILES
        main.cpp
        src/share/vm/prims/jni.cpp src/share/vm/prims/jni.h
        src/share/vm/runtime/threads/osThread.cpp src/share/vm/runtime/threads/osThread.h
        src/share/vm/runtime/threads/thread.cpp src/share/vm/runtime/threads/thread.h
        src/share/vm/utilities/globalDefinitions.cpp src/share/vm/utilities/globalDefinitions.h
        src/share/vm/utilities/debug.cpp src/share/vm/utilities/debug.h
        src/share/vm/runtime/globals.cpp src/share/vm/runtime/globals.h
        src/share/vm/runtime/os.cpp src/share/vm/runtime/os.h
        src/share/vm/runtime/mutex.cpp src/share/vm/runtime/mutex.h
        src/share/vm/runtime/threads/javaThread.cpp src/share/vm/runtime/threads/javaThread.h
        src/share/vm/runtime/threads/namedThread.cpp src/share/vm/runtime/threads/namedThread.h
        src/share/vm/runtime/threads/vmThread.cpp src/share/vm/runtime/threads/vmThread.h
        src/share/vm/runtime/init.cpp src/share/vm/runtime/init.h
        src/share/vm/memory/universe.cpp src/share/vm/memory/universe.h
        src/share/vm/gc/shared/collectedHeap.cpp src/share/vm/gc/shared/collectedHeap.h
        src/share/vm/memory/memRegion.cpp src/share/vm/memory/memRegion.h
        src/share/vm/runtime/vmStructs.cpp src/share/vm/runtime/vmStructs.h
        src/share/vm/utilities/exceptions.cpp src/share/vm/utilities/exceptions.h
        src/share/vm/oops/oop.cpp src/share/vm/oops/oop.h
        src/share/vm/oops/oopsHierarchy.cpp src/share/vm/oops/oopsHierarchy.h
        src/share/vm/oops/klass.cpp src/share/vm/oops/klass.h
        src/share/vm/runtime/handles.cpp src/share/vm/runtime/handles.h
        src/share/vm/gc/shared/gcCause.cpp src/share/vm/gc/shared/gcCause.h
        src/share/vm/gc/shared/generation.cpp src/share/vm/gc/shared/generation.h
        src/share/vm/gc/shared/genCollectedHeap.cpp src/share/vm/gc/shared/genCollectedHeap.h
        jre/java/lang/jre_object.cpp jre/java/lang/jre_object.h
        src/share/vm/gc/serial/defNewGeneration.cpp src/share/vm/gc/serial/defNewGeneration.h
        src/share/vm/gc/serial/tenuredGeneration.cpp src/share/vm/gc/serial/tenuredGeneration.h
        src/share/vm/gc/shared/space.cpp src/share/vm/gc/shared/space.h
        src/share/vm/runtime/atomic.cpp src/share/vm/runtime/atomic.h src/share/vm/classfile/classFileParser.cpp src/share/vm/classfile/classFileParser.h src/share/vm/utilities/vmError.cpp src/share/vm/utilities/vmError.h src/share/vm/classfile/classLoader.cpp src/share/vm/classfile/classLoader.h src/share/vm/oops/instanceKlass.cpp src/share/vm/oops/instanceKlass.h src/share/vm/runtime/symbol.cpp src/share/vm/runtime/symbol.h src/share/vm/classfile/systemDictionary.cpp src/share/vm/classfile/systemDictionary.h src/share/vm/utilities/ostream.cpp src/share/vm/utilities/ostream.h jre/java/lang/jre_core.h jre/java/lang/jre_class.cpp jre/java/lang/jre_class.h jre/java/lang/jre_metadata.cpp jre/java/lang/jre_metadata.h src/share/vm/prims/jvm.cpp src/share/vm/prims/jvm.h src/share/vm/runtime/arguments.cpp src/share/vm/runtime/arguments.h)
add_executable(MiniSpot ${SOURCE_FILES})