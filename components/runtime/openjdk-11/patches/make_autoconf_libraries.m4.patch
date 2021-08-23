$NetBSD$

Support SunOS/gcc.

diff -wpruN '--exclude=*.orig' a~/make/autoconf/libraries.m4 a/make/autoconf/libraries.m4
--- a~/make/autoconf/libraries.m4	1970-01-01 00:00:00
+++ a/make/autoconf/libraries.m4	1970-01-01 00:00:00
@@ -204,6 +204,7 @@ AC_DEFUN_ONCE([LIB_SETUP_MISC_LIBS],
 AC_DEFUN_ONCE([LIB_SETUP_SOLARIS_STLPORT],
 [
   if test "$OPENJDK_TARGET_OS" = "solaris" && test "x$BUILD_GTEST" = "xtrue"; then
+   if test "$TOOLCHAIN_TYPE" = "solstudio"; then
     # Find the root of the Solaris Studio installation from the compiler path
     SOLARIS_STUDIO_DIR="$(dirname $CC)/.."
     STLPORT_LIB="$SOLARIS_STUDIO_DIR/lib/stlport4$OPENJDK_TARGET_CPU_ISADIR/libstlport.so.1"
@@ -221,5 +222,6 @@ AC_DEFUN_ONCE([LIB_SETUP_SOLARIS_STLPORT
     fi
     AC_SUBST(STLPORT_LIB)
   fi
+  fi
 ])
 
