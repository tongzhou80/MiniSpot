
HotSpot manages assertions in a managed fashion, instead of using C++'s assert macro. It actively checks the condition
and if the condition fails, it then creates a VMError object, calls its method to document error message and trace
message to a file and then explicitly terminates the running thread.

`assert` and `guarantee` are two macros in HotSpot. `assert` macro is only defined when ASSERT is defined, so defining 
Assert produces a more strictly built version. `guarantee` is like `assert` except it's always executed.