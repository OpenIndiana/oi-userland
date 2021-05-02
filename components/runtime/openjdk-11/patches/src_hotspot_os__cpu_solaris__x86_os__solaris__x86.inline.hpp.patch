$NetBSD$

Support SunOS/gcc.

diff -wpruN '--exclude=*.orig' a~/src/hotspot/os_cpu/solaris_x86/os_solaris_x86.inline.hpp a/src/hotspot/os_cpu/solaris_x86/os_solaris_x86.inline.hpp
--- a~/src/hotspot/os_cpu/solaris_x86/os_solaris_x86.inline.hpp	1970-01-01 00:00:00
+++ a/src/hotspot/os_cpu/solaris_x86/os_solaris_x86.inline.hpp	1970-01-01 00:00:00
@@ -27,8 +27,16 @@
 
 #include "runtime/os.hpp"
 
+#ifdef _GNU_SOURCE
+inline jlong os::rdtsc() {
+  uint64_t res;
+  __asm__ __volatile__ ("rdtsc" : "=A" (res));
+  return (jlong)res;
+}
+#else
 extern "C" jlong _raw_rdtsc(); // In .il file
 
 inline jlong os::rdtsc() { return _raw_rdtsc(); }
+#endif
 
 #endif // OS_CPU_SOLARIS_X86_VM_OS_SOLARIS_X86_INLINE_HPP
