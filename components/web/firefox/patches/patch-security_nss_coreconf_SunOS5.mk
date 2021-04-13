diff --git a/security/nss/coreconf/SunOS5.mk b/security/nss/coreconf/SunOS5.mk
index ce9e2cb..b796e5d 100644
--- a/security/nss/coreconf/SunOS5.mk
+++ b/security/nss/coreconf/SunOS5.mk
@@ -81,9 +81,10 @@ NOMD_OS_CFLAGS += $(DSO_CFLAGS) $(OS_DEFINES) $(SOL_CFLAGS)
 
 MKSHLIB  = $(CC) $(DSO_LDOPTS) $(RPATH)
 ifdef NS_USE_GCC
-ifeq (GNU,$(findstring GNU,$(shell `$(CC) -print-prog-name=ld` -v 2>&1)))
-	GCC_USE_GNU_LD = 1
-endif
+# never use GNU LD on Solaris
+# ifeq (GNU,$(findstring GNU,$(shell `$(CC) -print-prog-name=ld` -v 2>&1)))
+# 	GCC_USE_GNU_LD = 1
+# endif
 endif
 ifdef MAPFILE
 ifdef NS_USE_GCC
