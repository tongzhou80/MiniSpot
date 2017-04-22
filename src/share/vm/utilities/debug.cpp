//
// Created by GentlyGuitar on 4/21/2017.
//

#include "debug.h"
#include "../runtime/thread.h"
#include "../runtime/globals.h"


void report_vm_error(const char* file, int line, const char* error_msg,
                     const char* detail_msg)
{
    if (Debugging || error_is_suppressed(file, line)) return;
    Thread* const thread = ThreadLocalStorage::get_thread_slow();
    VMError err(thread, file, line, error_msg, detail_msg);
    err.report_and_die();
}

void report_fatal(const char* file, int line, const char* message)
{
    report_vm_error(file, line, "fatal error", message);
}

void report_vm_out_of_memory(const char* file, int line, size_t size,
                             VMErrorType vm_err_type, const char* message) {
    if (Debugging) return;

    Thread* thread = ThreadLocalStorage::get_thread_slow();
    VMError(thread, file, line, size, vm_err_type, message).report_and_die();

    // The UseOSErrorReporting option in report_and_die() may allow a return
    // to here. If so then we'll have to figure out how to handle it.
    guarantee(false, "report_and_die() should not return here");
}

void report_should_not_call(const char* file, int line) {
    report_vm_error(file, line, "ShouldNotCall()");
}

void report_should_not_reach_here(const char* file, int line) {
    report_vm_error(file, line, "ShouldNotReachHere()");
}

void report_unimplemented(const char* file, int line) {
    report_vm_error(file, line, "Unimplemented()");
}

void report_untested(const char* file, int line, const char* message) {
#ifndef PRODUCT
    warning("Untested: %s in %s: %d\n", message, file, line);
#endif // !PRODUCT
}