$NetBSD$

Similar issue to https://bugs.openjdk.java.net/browse/JDK-8193056

diff -wpruN '--exclude=*.orig' a~/src/hotspot/share/gc/g1/g1Analytics.cpp a/src/hotspot/share/gc/g1/g1Analytics.cpp
--- a~/src/hotspot/share/gc/g1/g1Analytics.cpp	1970-01-01 00:00:00
+++ a/src/hotspot/share/gc/g1/g1Analytics.cpp	1970-01-01 00:00:00
@@ -23,6 +23,7 @@
  */
 
 #include "precompiled.hpp"
+#include "memory/allocation.inline.hpp"
 #include "gc/g1/g1Analytics.hpp"
 #include "gc/g1/g1Predictions.hpp"
 #include "runtime/os.hpp"
