//
// Created by GentlyGuitar on 4/21/2017.
//

#ifndef MINISPOT_DEBUG_H
#define MINISPOT_DEBUG_H



// assertions
#include <cstddef>

#ifdef ASSERT
#ifndef USE_REPEATED_ASSERTS
#define assert(p, msg)                                                       \
do {                                                                         \
  if (!(p)) {                                                                \
    report_vm_error(__FILE__, __LINE__, "assert(" #p ") failed", msg);       \
    BREAKPOINT;                                                              \
  }                                                                          \
} while (0)
#else // #ifndef USE_REPEATED_ASSERTS
#define assert(p, msg)
do {                                                                         \
  for (int __i = 0; __i < AssertRepeat; __i++) {                             \
    if (!(p)) {                                                              \
      report_vm_error(__FILE__, __LINE__, "assert(" #p ") failed", msg);     \
      BREAKPOINT;                                                            \
    }                                                                        \
  }                                                                          \
} while (0)
#endif // #ifndef USE_REPEATED_ASSERTS

// This version of assert is for use with checking return status from
// library calls that return actual error values eg. EINVAL,
// ENOMEM etc, rather than returning -1 and setting errno.
// When the status is not what is expected it is very useful to know
// what status was actually returned, so we pass the status variable as
// an extra arg and use strerror to convert it to a meaningful string
// like "Invalid argument", "out of memory" etc
#define assert_status(p, status, msg)                                        \
do {                                                                         \
  if (!(p)) {                                                                \
    report_vm_error(__FILE__, __LINE__, "assert(" #p ") failed",             \
                    err_msg("error %s(%d) %s", strerror(status),             \
                            status, msg));                                   \
    BREAKPOINT;                                                              \
  }                                                                          \
} while (0)

// Do not assert this condition if there's already another error reported.
#define assert_if_no_error(cond,msg) assert((cond) || is_error_reported(), msg)
#else // #ifdef ASSERT
  #define assert(p,msg)
  #define assert_status(p,status,msg)
  #define assert_if_no_error(cond,msg)
#endif // #ifdef ASSERT

// guarantee is like assert except it's always executed -- use it for
// cheap tests that catch errors that would otherwise be hard to find.
// guarantee is also used for Verify options.
#define guarantee(p, msg)                                                    \
do {                                                                         \
  if (!(p)) {                                                                \
    report_vm_error(__FILE__, __LINE__, "guarantee(" #p ") failed", msg);    \
    BREAKPOINT;                                                              \
  }                                                                          \
} while (0)

#define fatal(msg)                                                           \
do {                                                                         \
  report_fatal(__FILE__, __LINE__, msg);                                     \
  BREAKPOINT;                                                                \
} while (0)

// out of memory
#define vm_exit_out_of_memory(size, vm_err_type, msg)                        \
do {                                                                         \
  report_vm_out_of_memory(__FILE__, __LINE__, size, vm_err_type, msg);       \
  BREAKPOINT;                                                                \
} while (0)

#define ShouldNotCallThis()                                                  \
do {                                                                         \
  report_should_not_call(__FILE__, __LINE__);                                \
  BREAKPOINT;                                                                \
} while (0)

#define ShouldNotReachHere()                                                 \
do {                                                                         \
  report_should_not_reach_here(__FILE__, __LINE__);                          \
  BREAKPOINT;                                                                \
} while (0)

#define Unimplemented()                                                      \
do {                                                                         \
  report_unimplemented(__FILE__, __LINE__);                                  \
  BREAKPOINT;                                                                \
} while (0)

#define Untested(msg)                                                        \
do {                                                                         \
  report_untested(__FILE__, __LINE__, msg);                                  \
  BREAKPOINT;                                                                \
} while (0);


// types of VM error - originally in vmError.hpp
enum VMErrorType {
  INTERNAL_ERROR   = 0xe0000000,
  OOM_MALLOC_ERROR = 0xe0000001,
  OOM_MMAP_ERROR   = 0xe0000002
};

// error reporting helper functions
void report_vm_error(const char* file, int line, const char* error_msg,
                     const char* detail_msg = NULL);
void report_fatal(const char* file, int line, const char* message);
void report_vm_out_of_memory(const char* file, int line, size_t size,
                             VMErrorType vm_err_type, const char* message);
void report_should_not_call(const char* file, int line);
void report_should_not_reach_here(const char* file, int line);
void report_unimplemented(const char* file, int line);
void report_untested(const char* file, int line, const char* message);

void warning(const char* format, ...);

#endif //MINISPOT_DEBUG_H
