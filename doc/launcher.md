Creating a JVM and calling java program's main method in c++'s main is actually a type of calling Java static
method in native code. Therefore we can leverage jni's standard interface to launch a JVM instance in the launcher.
This is how JRockit and HotSpot implement the launcher.