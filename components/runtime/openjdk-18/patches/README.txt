This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for patches to build a project zero variant.

Most patches -p0

Forked off into the jdk18 repo; mainline is now jdk19.

18.0.2

Build broken by https://www.illumos.org/issues/14418. That did 2
things -  (1) exposed memcntl and meminfo by default, and (2) changed
the signature for memcntl from caddr_t to void so there's a
mismatch. The fix adopted is to modify the internal java signature for
memcntl to the new version, which still allows builds on older
releases as the old definition in sys/mman.h was effectively invisible
there.

JDK18:

Remove some unnecessary patches
src/java.base/unix/native/libjli/java_md.h
 - new comment is good
src/java.desktop/unix/native/common/awt/fontpath.c
 - shouldn't need to check for SunOS 5.8/5.9
Remove HS_DTRACE_WORKAROUND_TAIL_CALL_BUG, the bug it works around
  was fixed in 2008
Remove remaining SUNPRO and related MLIB_NO_LIBSUNMATH checks
src/java.desktop/unix/native/common/awt/X11Color.c
 - the complexity is over 20 years old and no longer relevant
make/autoconf/flags-cflags.m4
 - adding -DTRIMMED is useless
src/java.desktop/unix/native/libawt_xawt/awt/awt_InputMethod.c
 - unnecessary on illumos and current Solaris (and my S10 system too)
use the 64-bit rdtsc variant

18-29,18-30,18-31,18-32,18-33,18-34,18-35,18-36,18-37

No changes necessary

18-28

Now from jdk18 repo, should be in stabilisation phase.
Package it also now we've got this far.

Tidy ups:
Remove STLPORT, GLOBAL_LIBS (Studio remnants)

18-26, 18-27

Tiny amount of patch noise

18-25

Minor patch noise. The Foreign Function & Memory incubator doesn't
seem to have broken anything.

18-24

Add the 3 extra patches from omnios that fix up the signal handling
and remove the SIGSEGV warnings.

Tidy up, remove SPARC_WORKS

18-23

Fix src/hotspot/share/cds/classListParser.cpp

18-22

Tiny amount of patch noise

18-21

Tidy up prefetch_solaris_x86.inline.hpp

18-20

Tiny amount of patch noise

18-19

CDS header, moved one level down under _generic_header

18-18

os::get_default_process_handle() and os::dll_lookup() moved to posix

18-17

There's a Mac-specific change around vfork in
src/java.base/unix/native/libjava/ProcessImpl_md.c
I've temporarily simply switched the new __APPLE__ guard for the
__solaris__ one we had previously; this probably needs closer inspection.

The boot jdk needs to be 17 now.

A number of time related functions have been centralized into os_posix

18-16

os::have_special_privileges has been moved to posix

18-15

cgc_thread and pgc_thread merged into a single gc_thread.
Fixed a typo in the PLATFORM_API_SolarisOS_PCM.c fix.

18-14

src/java.desktop/share/classes/sun/font/TrueTypeGlyphMapper.java patch
wouldn't apply; I can't see why Solaris would need to be egregiously
different here so removed the patch.

Cleaned up a warning in PLATFORM_API_SolarisOS_PCM.c

18-13

A little patch noise.

18-12

Fix src/jdk.jlink/share/classes/jdk/tools/jlink/internal/Platform.java

18-10, 18-11

No changes

18-9

ResolverConfigurationImpl.java uses ArrayList, not LinkedList

18-8

A little patch noise.

18-7

Remove unused create_detachall_operation() that the build keeps
complaining about.

18-6

A bunch of Socket stuff appears to have been removed.

18-5

Remove os::bind_to_processor

18-4

A little patch noise.

The linker check has been hardened. It was always done wrong (it's using
gcc to get the linker version when it's actually looking for the as
version), but it now needs working around. We have the right assembler
in any case.

18-1, 18-2

No changes

18-0

rename bytes_solaris_x86.inline.hpp to bytes_solaris_x86.hpp
rename copy_solaris_x86.inline.hpp to copy_solaris_x86.hpp

Build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk17 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--enable-deprecated-ports=yes \
--with-jobs=3

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all
