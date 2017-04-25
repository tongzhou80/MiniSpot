
A VM is launched via JNI calls. Specifically in OpenJDK 9, the related files are 

- `./jdk/src/java.base/share/native/launcher/main.c` or `./build/linux-x86_64-normal-server-release/support/src/launcher/main.c`
  - calls JLI_Launch()
  
- `./jdk/src/java.base/share/native/libjli/java.c` or `./build/linux-x86_64-normal-server-release/support/src/launcher/java.c`
  - defines JLI_Launch() and other entry functions
  - finally, JavaMain is called in a new thread: `ContinueInNewThread0(JavaMain, threadStackSize, (void*)&args);`
  - JavaMain then calls JNI_CreateJavaVM etc.
  
For more on thread model, refer to  