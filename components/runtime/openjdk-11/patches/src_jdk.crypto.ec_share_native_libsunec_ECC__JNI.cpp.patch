$NetBSD$

Support SunOS/gcc. XXX!

diff -wpruN '--exclude=*.orig' a~/src/jdk.crypto.ec/share/native/libsunec/ECC_JNI.cpp a/src/jdk.crypto.ec/share/native/libsunec/ECC_JNI.cpp
--- a~/src/jdk.crypto.ec/share/native/libsunec/ECC_JNI.cpp	1970-01-01 00:00:00
+++ a/src/jdk.crypto.ec/share/native/libsunec/ECC_JNI.cpp	1970-01-01 00:00:00
@@ -39,6 +39,8 @@
 
 extern "C" {
 
+#define B_TRUE	_B_TRUE
+#define B_FALSE	_B_FALSE
 /*
  * Declare library specific JNI_Onload entry if static build
  */
