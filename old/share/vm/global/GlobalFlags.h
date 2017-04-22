//
// Created by tzhou on 11/5/16.
//

#ifndef MAGNOLIA_GLOBALFLAGS_H
#define MAGNOLIA_GLOBALFLAGS_H

#define DECLARE_DIAGNOSTIC_FLAG(type, name, value, doc)    extern type name;
#define DECLARE_DEVELOP_FLAG(type, name, value, doc)       extern type name;

#define DEFINE_DIAGNOSTIC_FLAG(type, name, value, doc)    type name = value;
#define DEFINE_DEVELOP_FLAG(type, name, value, doc)       type name = value;


/* Use short name (develop, etc) instead of the long macro name */
#define GENERATE_RUNTIME_FLAGS(develop, diagnostic) \
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

GENERATE_RUNTIME_FLAGS(DECLARE_DEVELOP_FLAG, DECLARE_DIAGNOSTIC_FLAG)

#endif //MAGNOLIA_GLOBALFLAGS_H
