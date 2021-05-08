$NetBSD$

Fix build on SunOS in C99 mode.

diff -wpruN '--exclude=*.orig' a~/src/java.desktop/share/native/libsplashscreen/libpng/pngpriv.h a/src/java.desktop/share/native/libsplashscreen/libpng/pngpriv.h
--- a~/src/java.desktop/share/native/libsplashscreen/libpng/pngpriv.h	1970-01-01 00:00:00
+++ a/src/java.desktop/share/native/libsplashscreen/libpng/pngpriv.h	1970-01-01 00:00:00
@@ -63,7 +63,7 @@
  * Windows/Visual Studio) there is no effect; the OS specific tests below are
  * still required (as of 2011-05-02.)
  */
-#ifndef _POSIX_SOURCE
+#if (!defined(__sun) || (__STDC_VERSION__-0 < 199901L)) && !defined(_POSIX_SOURCE)
 # define _POSIX_SOURCE 1 /* Just the POSIX 1003.1 and C89 APIs */
 #endif
 
