//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_GLOBALS_H
#define MINISPOT_GLOBALS_H



#define DECLARE_DIAGNOSTIC_FLAG(type, name, value, doc)    extern type name;
#define DECLARE_DEVELOP_FLAG(type, name, value, doc)       extern type name;

#define DEFINE_DIAGNOSTIC_FLAG(type, name, value, doc)    type name = value;
#define DEFINE_DEVELOP_FLAG(type, name, value, doc)       type name = value;


/* Use short name (develop, etc) instead of the long macro name */
#define GENERATE_RUNTIME_FLAGS(product, develop, diagnostic, iteration) \
  develop(bool, Debugging, false,                   \
         "")                                        \
  develop(bool, PrintConstantPool, true,            \
         "")                                        \
  develop(bool, PrintDisassembled, true,            \
         "")                                        \
  develop(bool, ThreadedInterpret, true,            \
         "")                                        \
  develop(bool, Object64BitModel, true,             \
         "")                                        \
  diagnostic(bool, ClassParsingVerbose, true,       \
         "")                                        \
  diagnostic(bool, ClassLoadingVerbose, true,       \
         "")                                        \
  diagnostic(bool, PrintDestruction, true,          \
         "")                                        \
  diagnostic(bool, PrintClassCreation, true,        \
         "")                                        \
  diagnostic(bool, PrintThreadCreation, true,       \
         "")                                        \
  iteration(bool, OnlyUseBootLoader, true,          \
         "")                                        \
  /* GC flags */                                    \
  develop(bool, UseSerialGC, true,                  \
  "Default serial GC")                              \
  develop(int, NewSize, 0,                          \
  "Size of eden in bytes")                          \
  develop(int, NewSizeInMB, 200,                    \
  "Size of eden in MB")                             \


GENERATE_RUNTIME_FLAGS(DECLARE_DEVELOP_FLAG, DECLARE_DIAGNOSTIC_FLAG, DECLARE_DEVELOP_FLAG, DECLARE_DIAGNOSTIC_FLAG)









#endif //MINISPOT_GLOBALS_H
