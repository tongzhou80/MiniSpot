
This post explains how a VM is created and initialized in MiniSpot.

A VM is created/destroyed by calling standard JNI interfaces. Both of them are just an array of pointers pointing to
a set of functions.
All the VM data structure will are created in the native memory globally, but the JNI program has no direct 
access to these data structures, they only operate through the interfaces.
`JavaVM` provides a series of actions related to the creation and destroying of the JVM. 
`JNIEnv` provides a series of class/object related operations by calling methods of the VM data structures.

We'll refer to the thread calling `JNI_CreateJavaVM` as `initial thread`. 
`JNI_CreateJavaVM` eventually calls `Threads::create_vm()`, which initializes some global structures, creates a 
JavaThread called `main thread`, which is the thread that actually executes Java code from the entry point. 
It then creates the `VM thread` and starts it. `VM thread` is the thread that does VM operations, such as invoking a 
GC.