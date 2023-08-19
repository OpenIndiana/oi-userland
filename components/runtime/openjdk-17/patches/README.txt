This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for patches to build a project zero variant.

Most patches -p0

JDK17:
17.0.8

Reinstate make/data/charsetmapping/stdcs-solaris, removal broke the
build.
See illumos-port-16.patch

Cleanup: remove TAR_CREATE_FILE_PARAM TAR_CREATE_EXTRA_PARAM

Cleanup: Removed another STLPORT reference

17.0.7

Minor patch noise. Removed an STLPORT patch.

17.0.6

Minor patch noise.

17.0.5

A number of functions centralised into os_posix

17.0.4

Build broken by https://www.illumos.org/issues/14418. That did 2
things -  (1) exposed memcntl and meminfo by default, and (2) changed
the signature for memcntl from caddr_t to void so there's a
mismatch. The fix adopted is to modify the internal java signature for
memcntl to the new version, which still allows builds on older
releases as the old definition in sys/mman.h was effectively invisible
there.


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

17.0.2

illumos-port-15.patch to fix the broken ld check

17-35

RC1, no changes

17-29,17-30,17-31,17-32,17-33,17-34

No changes

17-27,17-28

No changes. Packaged 17-28.

17-26

First from the jdk17 stabilisation repository. Same changes as in the
first jdk18 tag.

Remove extended file io workaround, it's 32-bit only

17-25

SecurityManager deprecation. Added suppression annotations (the way it
was done for Windows), and cleaned up the line number noise.

17-24

Line number noise.

Clean up some of the compiler warnings.

17-23

Line number noise.

os::os_exception_wrapper signature; last argument is a JavaThread not
a Thread. No impact as we don't actually use it.

17-22

Signature of reserve_memory_special and pd_reserve_memory_special has
changed to pass the page size. All we do is change the signature as
it's a no-op on solaris.

17-21

Line number noise.

17-20

Quite a lot of changes this time around.

No more aot, so remove patches for that.

src/hotspot/share/cds/classListParser.cpp has moved to
src/hotspot/share/cds/classListParser.cpp

suspend/resume has been essentially gutted

Assembler files are all .S not .s now; and the way it's called has
changed, so we need to just forget about forcing the studio assembler

Other changes made:

Also removed solstudio, which also cleans up C_FLAG_REORDER

Cleared out some of the sparc pieces

Gutted ucrypto

17-19

.mx.jvmci has gone, we don't need it anyway

Boot jdk requirement bumped to 16.
This triggers a lot of noisy
"SIGSEGV happened inside stack but outside yellow and red zone."
warnings during the build, but they appear harmless.

17-18

Don't patch jib-profiles.js. We don't use this, there aren't any AIX
entries, so putting ours in is a waste of effort.

Remove the nbproject patches; they're either wrong or irrelevant, or both.

The boolAtPut flag stuff is no more. The whole JVMFlag machinery has
been reworked. Renamed to set_bool.

Remove patching of JvmOverrideFiles.gmk when we then disable the
patch later.

17-17

No significant changes

17-16

Some patch noise this time. Some of the SPARC-related noise simply
removed.

17-15

No changes this time

17-14

Remove patch to c1_LIRAssembler.cpp as it's only for SPARC
Maybe lir_pack/lir_unpack could go too?

Tidied up Awt2dLibraries.gmk

More centralization into os_posix: os::die() os::shutdown() os::abort()

Tidy up some of the format noise

17-13

Remove the patches for lib-X11.m4; they're actually for S10, so we
don't want them anyway. And remove the patch to XRBackendNative.c
related to it which is also an S10 fixup.

os::fork_and_exec has been centralized

MetaspaceShared::is_in_trampoline_frame() has been removed

17-12

Remove saved_rbp_address_offset() from thread_solaris_x86.hpp

There's also evidence of xattr support on some platforms having been
added; it's not needed for the build so I've ignored it for now.

17-11

Fix memTracker.hpp; signature changed
Don't patch deoptimization.cpp, it was SPARC-specific

17-10

No significant changes

17-9

No significant changes

17-8

Man os:: functions were centralized into os_posix.inline.hpp, so
needed to remove our duplicates from os_solaris.inline.hpp and
os_solaris.cpp. Mostly the central copy was identical, the only odd
one was that the Solaris os::connect had some funky error handling

17-7

CLOCK_MONOTONIC is now just on.
Needed to remove os::supports_monotonic_clock() from os_solaris.inline.hpp
Remove javaTimeMillis() and javaTimeSystemUTC() and javaTimeNanos()
and javaTimeNanos_info() from os_solaris.cpp
Parker::park and Parker::unpark no longer compile, park.hpp has been
modified so we need to make sure _counter is present in
os_solaris.hpp; that makes it compile but it then crashes the jvm in there
The posix variant removed the guarantee in PlatformParker; we need to
do the same, fix the signature, and provide an implementation.
(The PlatformParker piece took a lot of effort.)

17-6

we now have perfMemory_posix.cpp, so perfMemory_solaris.ccp should be
removed or the build fails with multiply defined symbols

17-5

make/CompileJavaModules.gmk has mostly been gutted; ignore our patch
as it seem to build fine without

os.cpp needs to include alloca.h, see illumos-port-11.patch

17-4

src/jdk.hotspot.agent/share/classes/sun/jvm/hotspot/asm/Disassembler.java
has been refactored, but the new version appears to do the same thing
as we need in a platform-independent manner, so drop our patch

17-3

make/common/Modules.gmk has been completely redone; remove our patch

17-2

More memory stuff; pd_uncommit_memory pd_reserve_memory
pd_attempt_reserve_memory_at have changed signatures, with an extra
bool argument (that appears to be unused, at least linux and aix
don't make any use of it; this appears to be a Mac thing)

17-0/17-1

Quite a lot of refactoring of the toolchain stuff.

The page_size rework is really quite massive. The old _page_sizes was
an array you manipulated directly. It's now a set. This needs various
changes:

os::Solaris::is_valid_page_size() is just _page_sizes.contains()

Not strictly broken, but easy to fix: in mpss_sanity_check, we can
simplify the getpagesizes() stuff as we know we're modern

Rework listing of valid page sizes

This is a bit ugly because we don't really end up using the new
_page_sizes, but instead emulate the old array. Still, I can't find
examples of how the new way is supposed to work on any other platform.

Also need to implement print_memory_mappings, as a no-op (like AIX is)

That's enough to make it compile; it blows up with an arithmetic
exception, apparently inside apply_ergo(). In mpss_sanity_check, we
need to make sure page_size (which is really a pointer to
_large_page_size) is initialized to the largest valid page size.

Build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk16 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--enable-deprecated-ports=yes \
--with-jobs=3

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all
