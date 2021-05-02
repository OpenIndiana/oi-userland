$NetBSD$

Fix build on SunOS.

diff -wpruN '--exclude=*.orig' a~/src/hotspot/share/utilities/globalDefinitions_gcc.hpp a/src/hotspot/share/utilities/globalDefinitions_gcc.hpp
--- a~/src/hotspot/share/utilities/globalDefinitions_gcc.hpp	1970-01-01 00:00:00
+++ a/src/hotspot/share/utilities/globalDefinitions_gcc.hpp	1970-01-01 00:00:00
@@ -62,6 +62,7 @@
 #include <sys/procset.h>
 #include <ucontext.h>
 #include <setjmp.h>
+#include <inttypes.h>
 #endif // SOLARIS
 
 # ifdef SOLARIS_MUTATOR_LIBTHREAD
