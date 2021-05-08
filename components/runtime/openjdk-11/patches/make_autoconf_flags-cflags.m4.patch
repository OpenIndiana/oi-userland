$NetBSD$

Support for SunOS/gcc.

diff -wpruN '--exclude=*.orig' a~/make/autoconf/flags-cflags.m4 a/make/autoconf/flags-cflags.m4
--- a~/make/autoconf/flags-cflags.m4	1970-01-01 00:00:00
+++ a/make/autoconf/flags-cflags.m4	1970-01-01 00:00:00
@@ -41,8 +41,13 @@ AC_DEFUN([FLAGS_SETUP_SHARED_LIBS],
     SHARED_LIBRARY_FLAGS='-shared'
     SET_EXECUTABLE_ORIGIN='-Wl,-rpath,\$$ORIGIN[$]1'
     SET_SHARED_LIBRARY_ORIGIN="-Wl,-z,origin $SET_EXECUTABLE_ORIGIN"
+   if test "x$OPENJDK_TARGET_OS" = xsolaris; then
+    SET_SHARED_LIBRARY_NAME='-Wl,-h,[$]1'
+    SET_SHARED_LIBRARY_MAPFILE='-Wl,-M,[$]1'
+   else
     SET_SHARED_LIBRARY_NAME='-Wl,-soname=[$]1'
     SET_SHARED_LIBRARY_MAPFILE='-Wl,-version-script=[$]1'
+   fi
 
   elif test "x$TOOLCHAIN_TYPE" = xclang; then
     C_FLAG_REORDER=''
@@ -472,6 +477,7 @@ AC_DEFUN([FLAGS_SETUP_CFLAGS_HELPER],
 
   if test "x$TOOLCHAIN_TYPE" = xgcc; then
     ALWAYS_DEFINES_JVM="-D_GNU_SOURCE -D_REENTRANT"
+    ALWAYS_DEFINES_JDK="-D_GNU_SOURCE -D_REENTRANT -D_LARGEFILE64_SOURCE"
   elif test "x$TOOLCHAIN_TYPE" = xclang; then
     ALWAYS_DEFINES_JVM="-D_GNU_SOURCE"
   elif test "x$TOOLCHAIN_TYPE" = xsolstudio; then
