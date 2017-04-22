This project is out of personal interest and is currently under lazy development.

### Table of Contents
- [Introduction](#introduction)
- [Runtime Overview](#runtime-overview)
- [General Reference](#general-reference)


### Introduction
Magnolia JVM is an educational JVM for Java SE 8 Edition. It's designed as an teaching assisting tool for compiler
classes and runtime classes.

It supports a core subset of Java bytecodes, and shows the key designs and implementation of a Java virtual machine.

It aims to be helpful to teaching in many ways.
For example, it provides a clear interface of intermediate representation so that students could use the interface to
practing implementing static analysis and compiler optimizations.

The following section gives an overview of some vital topics.

### Runtime Overview
- [Bytecode Verification](doc/verification.md)
- [Method Frame](doc/methodframe.md)
- [Java Native Interface](doc/jni.md)

### General Reference
- JVM Specification for Java SE 8
- Java Langugage Specification
- [HotSpot Architecture](http://www.oracle.com/technetwork/java/whitepaper-135217.html#2)
- [CompressedOops](https://wiki.openjdk.java.net/display/HotSpot/CompressedOops)
- [Java HotSpot Virtual Machine Performance Enhancements](http://docs.oracle.com/javase/7/docs/technotes/guides/vm/performance-enhancements-7.html)
- Jikes RVM
- [JavaME CLDC](http://tech-insider.org/mobile/research/acrobat/0502.pdf)
- [JRockit](https://github.com/caoxudong/oracle_jrockit_the_definitive_guide/blob/master/contents.md) (zh-cn)
- Securing Java