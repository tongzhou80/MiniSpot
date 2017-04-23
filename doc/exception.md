
Some informative comments from exception.hpp

```
// This file provides the basic support for exception handling in the VM.                                                                                                                                          
// Note: We do not use C++ exceptions to avoid compiler dependencies and                                                                                                                                           
// unpredictable performance.                                                                                                                                                                                      
//                                                                                                                                                                                                                 
// Scheme: Exceptions are stored with the thread. There is never more                                                                                                                                              
// than one pending exception per thread. All functions that can throw                                                                                                                                             
// an exception carry a THREAD argument (usually the last argument and                                                                                                                                             
// declared with the TRAPS macro). Throwing an exception means setting                                                                                                                                             
// a pending exception in the thread. Upon return from a function that                                                                                                                                             
// can throw an exception, we must check if an exception is pending.                                                                                                                                               
// The CHECK macros do this in a convenient way. Carrying around the                                                                                                                                               
// thread provides also convenient access to it (e.g. for Handle                                                                                                                                                   
// creation, w/o the need for recomputation). 


// The ThreadShadow class is a helper class to access the _pending_exception                                                                                                                                       
// field of the Thread class w/o having access to the Thread's interface (for                                                                                                                                      
// include hierachy reasons).


// The CHECK... macros should be used to pass along a THREAD reference and to check for pending                                                                                                                    
// exceptions. In special situations it is necessary to handle pending exceptions explicitly,                                                                                                                      
// in these cases the PENDING_EXCEPTION helper macros should be used.                                                                                                                                              
//                                                                                                                                                                                                                 
// Macro naming conventions: Macros that end with _ require a result value to be returned. They                                                                                                                    
// are for functions with non-void result type. The result value is usually ignored because of                                                                                                                     
// the exception and is only needed for syntactic correctness. The _0 ending is a shortcut for                                                                                                                     
// _(0) since this is a frequent case. Example:                                                                                                                                                                    
//                                                                                                                                                                                                                 
// int result = this_function_may_trap(x_arg, y_arg, CHECK_0);                                                                                                                                                     
//                                                                                                                                                                                                                 
// CAUTION: make sure that the function call using a CHECK macro is not the only statement of a                                                                                                                    
// conditional branch w/o enclosing {} braces, since the CHECK macros expand into several state-                                                                                                                   
// ments! 

// The THROW... macros should be used to throw an exception. They require a THREAD variable to be                                                                                                                  
// visible within the scope containing the THROW. Usually this is achieved by declaring the function                                                                                                               
// with a TRAPS argument. 

```