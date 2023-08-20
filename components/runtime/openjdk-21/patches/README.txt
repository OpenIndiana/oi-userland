This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for note on a project zero variant.

JDK 21 now we're in rampdown.

Issues known that indicate serious bugs, likely due to not integrating
loom correctly as they date back to that change. Specifically, I
suspect we need to provide a working DefaultPoller implementation
rather than the current stub.
* jshell doesn't work
* illuminate doesn't work

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
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk20 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--with-source-date=current \
--with-jobs=3 \
DATE=/usr/gnu/bin/date \
STRIP=/usr/gnu/bin/strip

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all
