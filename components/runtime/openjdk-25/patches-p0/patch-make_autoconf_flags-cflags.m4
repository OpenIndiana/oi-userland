$NetBSD$

Support for SunOS/gcc.

--- make/autoconf/flags-cflags.m4.orig	2019-01-08 09:40:27.000000000 +0000
+++ make/autoconf/flags-cflags.m4
@@ -42,7 +42,13 @@ AC_DEFUN([FLAGS_SETUP_SHARED_LIBS],
     # overridden using LD_LIBRARY_PATH. See JDK-8326891 for more information.
     SET_EXECUTABLE_ORIGIN='-Wl,-rpath,\$$ORIGIN[$]1 -Wl,--disable-new-dtags'
     SET_SHARED_LIBRARY_ORIGIN="-Wl,-z,origin $SET_EXECUTABLE_ORIGIN"
+   if test "x$OPENJDK_TARGET_OS" = xsolaris; then
+    SET_EXECUTABLE_ORIGIN='-Wl,-rpath,\$$ORIGIN[$]1'
+    SET_SHARED_LIBRARY_ORIGIN="-Wl,-z,origin $SET_EXECUTABLE_ORIGIN"
+    SET_SHARED_LIBRARY_NAME='-Wl,-h,[$]1'
+   else
     SET_SHARED_LIBRARY_NAME='-Wl,-soname=[$]1'
+   fi
 
   elif test "x$TOOLCHAIN_TYPE" = xclang; then
     if test "x$OPENJDK_TARGET_OS" = xmacosx; then
@@ -66,7 +72,11 @@
       if test "x$OPENJDK_TARGET_OS" = xlinux; then
         SET_EXECUTABLE_ORIGIN="$SET_EXECUTABLE_ORIGIN -Wl,--disable-new-dtags"
       fi
-      SET_SHARED_LIBRARY_NAME='-Wl,-soname=[$]1'
+      if test "x$OPENJDK_TARGET_OS" = xsolaris; then
+        SET_SHARED_LIBRARY_NAME='-Wl,-h,[$]1'
+      else
+        SET_SHARED_LIBRARY_NAME='-Wl,-soname=[$]1'
+      fi
 
       # arm specific settings
       if test "x$OPENJDK_TARGET_CPU" = "xarm"; then
@@ -509,6 +519,7 @@ AC_DEFUN([FLAGS_SETUP_CFLAGS_HELPER],
 
   if test "x$TOOLCHAIN_TYPE" = xgcc; then
     ALWAYS_DEFINES_JVM="-D_GNU_SOURCE -D_REENTRANT"
+    ALWAYS_DEFINES_JDK="-D_GNU_SOURCE -D_REENTRANT -D_LARGEFILE64_SOURCE"
   elif test "x$TOOLCHAIN_TYPE" = xclang; then
     ALWAYS_DEFINES_JVM="-D_GNU_SOURCE"
   elif test "x$TOOLCHAIN_TYPE" = xmicrosoft; then
