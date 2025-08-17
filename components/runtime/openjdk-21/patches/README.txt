This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for note on a project zero variant.

21.0.8

Poller implDeregister() signature change.

Need extra pipewire patch.

Cleanup: remove unused check_addr0_done.

Cleanup: remove the Studio type linkage block from the gcc header.

Cleanup: remove the unshuffle_list.txt hunk.

Cleanup: Correct DTRACE_INSTRUMENTED_OBJS.

Fix: Correct type argument to sema_init.

Cleanup: Duplicate check for SC_CLK_TCK.

21.0.7

Minor patch noise.

Needed to fix up jline due to updates, to match changes in other
platforms.

Fix incorrect LDFLAGS in TestFilesCompilation.gmk, see
illumos-port-28.patch

os::print_tos_pc() has been centralized, so remove our copy.

Cleanup: Move the mapfiles (symbol files) to the right place.

Cleanup: Remove the use of lp rather than lpr; all supported systems
can or even should be using CUPS rather than legacy lp.

Cleanup: Remove /usr/bin/sh override in PrintServiceLookupProvider.java.

Cleanup: Define -D_REENTRANT for non-gcc (ie clang) builds

Cleanup: Remove unused global UseOSErrorReporting.

Cleanup: Remove long unused sysThreadAvailableStackWithSlack()

21.0.6

Minor patch noise.

Cleanup: remove audio solaris 7 compatibility code

Cleanup: use pset_getloadavg() directly

Cleanup: Remove SolarisX86JavaThreadPDAccess, it's for 32-bit.

Cleanup: allow fastdebug builds, see fastdebug.patch

Cleanup: remove unused JSIG_VERSION_1_4_1 define

Cleanup: remove unused SOLARIS_MUTATOR_LIBTHREAD hunk

21.0.5

Drop the png patch. It no longer applies and appears unnecessary with
the png update.

Need to provide an implementation of pd_pretouch_memory()

Cleanup: src/hotspot/os/solaris and src/hotspot/os_cpu/solaris_x86
split out into separate restore patches.

Cleanup: format warning in print_memory_info()

Cleanup: use jdk21 to build jdk21, as it's LTS.

21.0.4

Removed last remnants of extended_FILE_stdio, it's unused as 32-bit
only, and the code to enable it had already been removed.

Remove local copies of os::dont_yield() os::naked_yield()

Centralization of breakpoint()

21.0.3 respin 2

Provide a working DefaultPoller implementation rather than the current
stub in order to get loom fully working. (Courtesy of Jasper Siepkes.)

21.0.3 respin 1

Fixed the patch for src/java.base/unix/classes/java/lang/ProcessImpl.java
which fixes the startup hang in jshell and illuminate (and hopefully
the minecraft reports)

Cleanup: missed the dropping of TIERED in 17+8, it's now
COMPILER1_AND_COMPILER2

21.0.3

The smartcardio patch failed to apply. It's been reworked, but I can't
see any evidence of this change in mainline so it's not a
backport. Fixed up, mostly it's indented one stop deeper.

New undefined symbol os::pd_dll_unload; copy the implementation from
os_linux.cpp (backported from jdk23).

os::prepare_native_symbols() has been added, provide a no-op implementation
(backported from jdk22)

21.0.2

A bit of shuffling in ProcessHandleImpl_unix.c

21.0.1

Now jdk21u.

We need an implementation of os::can_trim_native_heap() and
trim_native_heap(); simply add a stub in os_solaris.inline.hpp to
return false like pretty much every other platform except linux does.

21+34, 21+35

No changes.

21+33

No changes in regular port.

Fix zero port; see Atomic and print_register_info change in jdk 21+23

21+27, 21+28, 21+29, 21+30, 21+31, 21+32

No changes.

21+26

Forked to the jdk21 stabilisation repo.

Some patch noise.

Add null implementation of jfr_report_memory_info()

It appears that pipewire has been imported; see illumos-port-27.patch
for a minor tweak to make it compile

21+25

Bit of patch noise

21+24

It appears that jline https://github.com/jline/jline3 has been
imported
See illumos-jline.patch for implementation

21+23

Extensive rework of
src/jdk.jlink/share/classes/jdk/tools/jlink/internal/Platform.java
dropped the existing patch, which no longer applies

Atomic, fetch_and_add has been renamed to fetch_then_add

os_solaris_x86.cpp, print_register_info has been reworked; copy the
linux_x86 changes (the function was the same as linux was before).

Need to add static julong free_memory(); use available_memory() as I
can't see why they would be different.

21+21

OperatingSystemProps has become PlatformProps, and restructured a bit.

21+20

Boot jdk bumped to 20.

21+19

More OperatingSystem changes
src/java.desktop/share/classes/sun/awt/FontConfiguration.java
src/java.desktop/share/classes/sun/awt/OSInfo.java
src/java.desktop/share/classes/sun/font/FontUtilities.java
src/java.desktop/unix/classes/sun/print/PrintServiceLookupProvider.java
src/java.desktop/unix/classes/sun/print/UnixPrintJob.java

Delete the patch for src/java.desktop/share/classes/sun/font/CMap.java,
it's very specific to openwin. Ditto
src/java.desktop/share/classes/sun/font/SunFontManager.java

Copy illumos-port-22.patch from openjdk20 to illumos-port-26.patch
here to ensure INT_MAX is defined.

21+18

More OperatingSystem changes. Fixed patches to:
src/java.security.jgss/share/classes/sun/security/jgss/wrapper/SunNativeProvider.java
src/java.security.jgss/share/classes/sun/security/krb5/Config.java
src/jdk.charsets/share/classes/sun/nio/cs/ext/JISAutoDetect.java
The JISAutoDetect.java needed an extra fi as there's a whole extra method.

Also fix
src/jdk.sctp/unix/classes/sun/nio/ch/sctp/SctpNet.java
where Solaris was actually the only consumer.
FIXME: the SctpNet fix is a non-portable hack, the code won't work on
any other platform, as I've unconditionally patched it. This ought to
use the OperatingSystem, but that would involve messing around with
src/java.base/share/classes/module-info.java and
src/java.base/share/lib/security/default.policy
which seems excessively fussy and security-dependent

(Looking at our patches, there are many more opportunities to use the
central OperatingSystem machinery.)

Missed the patch from 21+17 for javaThread.cpp; added illumos-port-25.patch

21+17

Remove anything related to libfdlibm, as that's gone entirely

Remove tribblix-flags-ldflags2.patch; the patched solaris behaviour is
now the default.

src/hotspot/share/runtime/javaThread.cpp uses alloca() so needs the header

test/jdk/java/io/File/libGetXSpace.c uses statfs() which ought to be
statvfs() for us, see illumos-port-24.patch

21+16

Triggered by changes in SdpSupport.java, add SunOS support to
src/java.base/share/classes/jdk/internal/util/OperatingSystem.java
src/java.base/share/classes/jdk/internal/util/OperatingSystemProps.java.template
See illumos-port-23.patch

The new OperatingSystem support has also been used in
src/java.base/unix/classes/java/lang/ProcessImpl.java
which needs a completely different patch

And src/java.base/unix/classes/sun/net/PortConfig.java needs fixing.

Cleanup: merge and remove illumos-signal-2.patch and
illumos-signal-3.patch

Cleanup: remove TAR_CREATE_FILE_PARAM TAR_CREATE_EXTRA_PARAM

Cleanup: remove ThreadPriorityVerbose (was Solaris-only)

Cleanup: remove UseDetachedThreads (always true)

21+15

Trivial patch noise. NULL -> nullptr changes still to do.

21+14

Minor patch noise. NULL -> nullptr changes still to do.

CodeCache::mark_all_nmethods_for_deoptimization() changed.

21+13

Trivial patch noise. NULL -> nullptr changes still to do.

Remove the deprecated platform configure option, as we'll run into
trouble if the 32-bit windows deprecation reuses it.

21+12

Reinstate make/data/charsetmapping/stdcs-solaris, removal broke the build

NULL -> nullptr changes still to do.

21+11

Trivial patch noise. NULL -> nullptr changes still to do.

os::numa_has_static_binding() has been removed.

21+10

Trivial patch noise. NULL -> nullptr changes still to do.

21+9

Trivial patch noise. This was also an update where NULL was being
replaced with nullptr on a large scale. The initial build did not make
those changes for the solaris port.

21+7, 21+8

Trivial patch noise

21+6

Remove unused os::get_page_info().
Add a no-op for os::numa_get_group_ids_for_range().

21+5

Minor patch noise.

The JAVA_WARNINGS_ARE_ERRORS note appears to only occur on some build
machines, which is very odd.

21+4

The reorderMap in MFontConfiguration.java now needs to construct
String[] by hand rather than using FontConfiguration.split()

Something odd has changed that's broken my build; I needed to add
JAVA_WARNINGS_ARE_ERRORS=""
to the gmake command. Otherwise -Werror turns all java warnings into
errors and fails the build. The thing is that there's nothing new here.

21+2, 21+3

Trivial patch noise

21+0

Starting fairly clean.

VM_Version::page_size_count() has been removed, but it's only returning
a constant so we can easily handle that.

Build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk21 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--with-source-date=current \
--with-jobs=4 \
DATE=/usr/gnu/bin/date \
STRIP=/usr/gnu/bin/strip

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all
