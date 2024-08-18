 This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for note on a project zero variant.

JDK 23 now that jdk22 has been forked off.

Cleanup: Removed last remnants of extended_FILE_stdio, it's unused as 32-bit
only, and the code to enable it had already been removed.

23+27, 23+28, 23+29, 23+30, 23+31, 23+32, 23+33, 23+34, 23+35, 23+36

No changes.

23+26

Branched off now that jdk24 is mainline.

Cleanup: switch to SolarisEventPortPoller

Fixed the patch for src/java.base/unix/classes/java/lang/ProcessImpl.java
which fixes the startup hang in jshell and illuminate (and hopefully
the minecraft reports)

23+24

Saw insufficient memory build failures even with jobs=4.

23+24

Saw build failures with jobs=8:
There is insufficient memory for the Java Runtime Environment to
continue.
(This has been seen in both the bootstrap compiler and the newly built
compiler, so I don't think it's a recent code change, but is more
likely related to changes in the build process.)

23+23

JLine updated, our patch no longer needed (or useful).

23+22

os::create_binary_file() centralized

Tiny tweak to align attachListener code

23+21

Tiny amount of patch noise.

Remove local copies of os::dont_yield() os::naked_yield()

Saw build failures with jobs=12:
There is insufficient memory for the Java Runtime Environment to continue.
But clean build if dialled down to 8.

23+20

Fixed up attachListener filename.

Unsafe arraycopy and memory access function and variable renaming.

Blocker type change in EPollSelectorImpl.java

Removed illumos-port-4.patch, the solaris-specific code
(SolarisUserDefinedFileAttributeView) that used the extra
newFileChannel() variant was removed in jdk 20+4, and now fails to
build.

23+19

Much much more mucking around with Makefiles.

Hunk from make/common/MakeBase.gmk now moved to make/common/FileUtils.gmk

Rework of make/common/native/DebugSymbols.gmk makes our patch unnecessary.

Awt2dLibraries.gmk renamed to AwtLibraries.gmk, and none-Awt split out
into ClientLibraries.gmk

The attachListener centralization is incorrectly guarded. It only
implements bsd and linux, so should be guarded as such, not !aix
See illumos-attachlistener.patch
(The file also has the wrong name which will get corrected.)

With the shuffling around, it can't link properly, had to add libjvm
explicitly in a few places. There must be a better way to do this.

23+18

Minor tweak to one line in os_solaris_x86.cpp to match changes in
Linux.

23+17

More mucking around with Makefiles.

Need to remove notproduct from RUNTIME_OS_FLAGS in globals_solaris.hpp

Minimum boot jdk now bumped to jdk22.

23+16

Much more mucking around with Makefiles.

Centralization of breakpoint()

The patch for make/modules/jdk.net/Lib.gmk was broken and unnecessary,
as the Solaris libextnet was removed back in jdk15. It was unnecessary
because there was a guard that prevented it being built on Solaris,
That guard has been removed, and that causes the build to fail because
there isn't a Solaris libextnet. So reinstate a guard to prevent
libextnet being built on Solaris.

23+15

Significant rework of the Makefiles.

Remove the Launcher.gmk patch as it was guarded by a linux check,
delivering jexec which we don't

Remove patch-make_launcher_LauncherCommon.gmk,
patch-make_lib_LibCommon.gmk, and fix-TestFilesCompilation.patch as the
code being patched no longer exists

The rework benefits us because we only have to patch out the incorrect
--exclude-libs usage in one place

Cleanup: reduce gratuitous formatting differences between our
attachListener_solaris.cpp and other platforms, without changing any code

23+14

A little bit of patch cleanup needed due to removal of the xlc toolchain.

More use of "isTargetOsType" rather than enumerating the
OS variants individually, which actually helps solaris.

Some removals of local RESTARTABLE definition which moves the lines around.

SKIP_SPACE was removed in src/java.base/unix/native/libjava/TimeZone_md.c,
just inline it.

Another gnuism of --exclude-libs in make/common/TestFilesCompilation.gmk
to hide, see fix-TestFilesCompilation.patch

23+13

More work on make/autoconf/flags-cflags.m4, need to make sure that the
misguided --disable-new-dtags doesn't apply to us.

23+12

More rework of the build system.
flags-cflags.m4 use of --version-script and SET_SHARED_LIBRARY_MAPFILE
has been removed. make/hotspot/lib/JvmMapfile.gmk has been removed and
there's a static mapfile at make/data/hotspot-symbols/version-script.txt
referenced as HOTSPOT_VERSION_SCRIPT in make/hotspot/lib/CompileJvm.gmk
That version-script.txt isn't a valid solution for us, and is rejected
by our ld, so ignore the mapfile stuff completely.

If we do need to look at this again, the commit that did it is here:
https://github.com/openjdk/jdk/commit/da14aa463b8fcd56ba1f1a4cdb3e3f7b19f78964

Cleanup: drop the comment-only change to make/langtools/build.xml

23+11

Extensive rework of NativeCompilation.gmk, the hunk we want is now in
make/common/native/DebugSymbols.gmk

The file make/scripts/compare_exceptions.sh.incl is now empty, so
don't try and patch it

os::pd_remap_memory() has been removed
os::pd_map_memory() os::pd_unmap_memory() have been centralized into os_posix

23+10

Patch noise; much of it associated with cleaning up the 64-bit
function name usage in Linux and AIX

Remove #include of code/icBuffer.hpp, as the file has gone

Cleanup: missed the dropping of TIERED in 17+8, it's now
COMPILER1_AND_COMPILER2

23+9

Needed to implement os::total_swap_space and os::free_swap_space
This uses the (undocumented in the man page) swapctl(SC_AINFO, &ai)
call, as in the doswap() function in usr/src/cmd/swap/swap.c

23+8

Implement os::pd_pretouch_memory(), copying the basic implementation
from aix.

23+7

Tidied up the fatal(dlerror()) warning.

23+6

New undefined symbol os::pd_dll_unload; copy the implementation from
os_linux.cpp

23+5

Trivial patch noise.

23+4

Remove unused and undefined os::can_execute_large_page_memory() from
os_solaris.cpp

23+3

Trivial patch noise

23+0, 23+1, 23+2

No changes needed, identical to 22+27.

Build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk22 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--with-source-date=current \
--with-jobs=4 \
DATE=/usr/gnu/bin/date \
STRIP=/usr/gnu/bin/strip

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all
