This is derived from the pkgsrc-joyent set for openjdk11
https://github.com/joyent/pkgsrc-joyent/tree/master/openjdk11

All patches -p0

This set of patches for jdk11u

11.0.19

Rework of the way the build and target OS is identified.

11.0.16

Fix the memcntl signature for recent illumos changes.

11.0.13

Just a little patch noise to tidy up

11.0.12 - remove illumos-cpu_microcode_revision.patch, there's an
equivalent stub fix applied upstream so we don't need to do it

Removed:

patch-make_autoconf_flags-other.m4 - breaks as
patch-make_autoconf_lib-bundled.m4 - breaks zlib
patch-make_lib_Lib-java.instrument.gmk - remove -liconv
patch-make_lib_Lib-jdk.jdwp.agent.gmk - remove -liconv
patch-make_autoconf_flags-ldflags.m4 - broken as of 11.0.7

Modified:

patch-make_lib_Awt2dLibraries.gmk - remove -liconv
patch-make_launcher_LauncherCommon.gmk - breaks zlib
patch-make_launcher_Launcher-jdk.pack.gmk - breaks zlib

Anything named tribblix* is my additional patches:

tribblix-attachListener_solaris.patch
  fixes incorrect arguments

tribblix-flags-cflags.patch 
  remove SSP

tribblix-Launcher-jdk.patch
tribblix-LauncherCommon.patch
  KPIC -> fPIC

tribblix-agent-mt.patch
  remove -mt

tribblix-flags-ldflags.patch
tribblix-flags-ldflags2.patch
  replace the broken patch-make_autoconf_flags-ldflags.m4

tribblix-flags-ldflags3.patch
  don't use -pie or --allow-shlib-undefined

tribblix-demangle1.patch
tribblix-demangle2.patch
tribblix-demangle3.patch
tribblix-demangle4.patch
  use the gcc demangle rather than the Studio demangle

tribblix-sparc1.patch
  some basic fixes necessary (but not sufficient) for a SPARC build

tribblix-sparc2.patch
  fixes to enable a sparc build with gcc; it's possible that using the
  atomic_linux_sparc.hpp from linux_sparc rather than
  atomic_solaris_sparc.hpp from solaris_sparc may also be required 

Build:

Use a jdk11 build as a bootstrap (from Liberica or Azul should also
work if your distro doesn't have one yet).

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk11 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-hotspot-gtest --disable-dtrace \
--disable-warnings-as-errors

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all
