### Method Frame

### JValue
The slot type used in locals, object fields, constant pool and operand stack is termed JValue in this document.
An intuitive implementation approach is to implement different java primitive types as a C/C++ union. This is how
HotSpot implements it (src/share/vm/interpreter/bytecodeInterpreter.hpp). To differentiate one-word type (int, float, char, byte, short, double, long) and two-word type
(long and double), two unions are needed. Java does not have union type, so Jikes creates an Address type and passes
an additional argument to indicate type of address.

### Local variable array

