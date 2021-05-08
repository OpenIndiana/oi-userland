$NetBSD$

Shell portability.

diff -wpruN '--exclude=*.orig' a~/make/autoconf/jdk-options.m4 a/make/autoconf/jdk-options.m4
--- a~/make/autoconf/jdk-options.m4	1970-01-01 00:00:00
+++ a/make/autoconf/jdk-options.m4	1970-01-01 00:00:00
@@ -207,7 +207,7 @@ AC_DEFUN_ONCE([JDKOPT_SETUP_JDK_OPTIONS]
   AC_ARG_WITH(cacerts-file, [AS_HELP_STRING([--with-cacerts-file],
       [specify alternative cacerts file])])
   AC_MSG_CHECKING([for cacerts file])
-  if test "x$with_cacerts_file" == x; then
+  if test "x$with_cacerts_file" = x; then
     AC_MSG_RESULT([default])
   else
     CACERTS_FILE=$with_cacerts_file
