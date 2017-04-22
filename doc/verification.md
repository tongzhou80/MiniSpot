This page explains the design choice of bytecode verification in several popular VM implementations.

### Jikes RVM
Jikes RVM chooeses not to support bytecode verification => [FAQ](http://www.jikesrvm.org/FAQ/)

### HotSpot VM
There are currently two methods of analyzing the bytecodes to determine the types and number of operands
that will be present for each instruction.

- Type inference
  - Traditional, potentially takes more than one pass
  - Perform an abstract interpretation of each bytecode and merge type states at branch targets or exception handles.
  - Iterates over the bytecode until a steady state for the types are found
  - If a steady state cannot be found, or if the resulting types violate some bytecode constraint, throw VerifyError.

- Type verification
  - Introduced in OpenJDK 6 and forced in OpenJDK 7, only one pass
  - The compiler provides the steady-state type information for each branch or exception target, via the code attribute, StackMapTable.
  - The StackMapTable consists of a number of stack map frames, each which indicates the types of the items on the expression stack and in the local variables at some offset in the method.
  - Previously used by JavaME CLDC. Since it it smaller and faster, this method of verification is built directly in the VM itself.

- Requirements
  - Classfile version number \< 50 (prior to JDK6)
    - Use the traditional type inference
  - Classfile version number \> 50
    - the StackMapTable attributes will be present and the new verifier will be used
  - Because of the possibility of older external tools that might instrument the bytecode but neglect to update the StackMapTable attribute, certain verification errors that occur during type-checking verification may failover to the type-inference method. Should that pass succeed, the class file will be verified.

> A Java Virtual Machine implementation cannot choose to resort to type inference in once case and not in another. It must either reject class files that do not verify via type checking, or else consistently failover to the type inferencing verifier whenever type checking fails.

### CLDC (KVM)
CLDC White paper says...

CLDC requires that a Java VM be able to identify and reject invalid classfiles. However, since the standard classfile verification approach defined by J2SE is too memory-consuming for small devices, CLDC defines an alternative mechanism for classfile verification.
In this alternative, each method in a downloaded Java classfile contains a “stackmap” attribute. This attribute is newly-defined in CLDC and is not defined by The Java Virtual Machine Specification. Typically, this attribute is added to standard classfiles by a “pre-verification” tool that analyzes each method in the classfile. Pre-verification is typically performed on a server or desktop system before the classfile is downloaded to the device. The stack map attribute increases the size of a classfile by approximately 5%.

### Reference
- [An explanation of stack map frame on stackoverflow](http://stackoverflow.com/questions/25109942/is-there-a-better-explanation-of-stack-map-frames)
- [HotSpot Bytecode Verifier](http://openjdk.java.net/groups/hotspot/docs/RuntimeOverview.html#Bytecode%20Verifier%20and%20Format%20Checker|outline)
- JVM SE8 Specification
- [CLDC white paper](http://tech-insider.org/mobile/research/acrobat/0502.pdf)