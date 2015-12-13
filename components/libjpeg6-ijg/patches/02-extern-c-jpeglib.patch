Description: Wrap jpeglib.h with extern "C" {} if __cplusplus is defined.
 Wrap jpeglib.h inside extern "C" { ... } if the compiler
 defines __cplusplus.
Author: Bill Allombert <ballombe@debian.org>
Origin: Debian
Forwarded: not-needed
Last-Update: 2010-06-03
Index: libjpeg6b-6b1/jpeglib.h
===================================================================
--- libjpeg6b-6b1.orig/jpeglib.h	2010-06-03 19:02:32.000000000 +0200
+++ libjpeg6b-6b1/jpeglib.h	2010-06-03 19:02:37.000000000 +0200
@@ -13,6 +13,10 @@
 #ifndef JPEGLIB_H
 #define JPEGLIB_H
 
+#ifdef __cplusplus
+extern "C" {
+#endif
+
 /*
  * First we include the configuration files that record how this
  * installation of the JPEG library is set up.  jconfig.h can be
@@ -1093,4 +1097,8 @@
 #include "jerror.h"		/* fetch error codes too */
 #endif
 
+#ifdef __cplusplus
+}
+#endif
+
 #endif /* JPEGLIB_H */
