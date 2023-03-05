This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for note on a project zero variant.

20+29, 20+30, 20+31, 20+32, 20+33

No changes; now in rampdown phase 2

20+28

Trivial patch noise

20+27

Forked off, now in rampdown phase 1.

VM_Version::page_size_count() has been removed, but it's only returning
a constant so we can easily handle that.

20+25, 20+26

Minor patch noise

20+24

os::supports_sse() has been removed

20+23

ExtendedDTraceProbes has been removed. Which removes 
DTrace::set_extended_dprobes() as well.

20+22

Now need to force gnu strip via setting STRIP

20+21

Remove os::dll_file_extension()

Modest amount of patch noise

20+20

Trivial patch noise.

20+19

Boot jdk updated to jdk19.

Remove patch for hsdis Makefile, as it's been removed.

20+18

Trivial patch noise

20+17

src/java.base/unix/native/libnio/ch/FileChannelImpl.c
has been removed, so don't patch it. However:

FileDispatcherImpl has been split out into a shared
UnixFileDispatcherImpl plus platform-specific FileDispatcherImpl, so
we need our own implementation, and that includes parts of what would
have been FileChannelImpl.c, the new files are
src/java.base/solaris/classes/sun/nio/ch/FileDispatcherImpl.java and 
src/java.base/solaris/native/libnio/ch/FileDispatcherImpl.c, and all
we need to do is implement our copy of transferTo0 from the old
FileChannelImpl.c, see illumos-port-21.patch

Remove tribblix-wait.patch, the patched file is no more.

20+15, 20+16

Trivial patch noise

20+14

Bit of patch noise, update cflags from c99 (in our case, gnu99) to c11
(in our case, gnu11)

20+13

Remove ProcDebuggerLocal.java, the whole ProcDebugger has gone. So
remove all solaris support from HotSpotAgent.java as a
consequence. This also means that libsaproc is no more, and
tribblix-demangle4.patch isn't needed either

CodeCache::find_blob_unsafe() is now just CodeCache::find_blob()

Fixes from build attempt with clang - comments in .S use # not /;
register specifier is deprecated; use the right linker flags.

20+12

Trivial patch noise.

20+11

page_size() has been centralised

Remove more 32-bit code from os_solaris_x86.cpp

Tidying up old 32-bit code

20+10

Quite a lot of changes here.

The layout of the os class has changed a bit
Needed to patch os.hpp, see illumos-port-20.patch
but lots of other changes needed.

Remove some 32-bit code from os_solaris_x86.cpp

Move correct_stack_boundaries_for_primordial_thread() which is in
os::Solaris from the shared thread.cpp into our own os_solaris.cpp

Use pthread variants directly in attachListener_solaris.cpp

More use of the posix PlatformMutex

Remove comment-only patch to os.hpp to simplify maintenance

Remove illumos-port-8.patch, as the platform guard was reworked to be
correct by default

Test builds with different C standards. With -std=gnu11, everything is
fine; with -std=c11 or c99, build fails with our own headers (around
signals, eg sigaction and friends, and presumably more).

Remove src/hotspot/os_cpu/solaris_x86/count_trailing_zeros_solaris_x86.hpp

Tidy up atomic_solaris_x86.hpp, remove Studio support;
solaris_x86_64.il can also be removed.

Tidy up bytes_solaris_x86.hpp, remove 32-bit and Studio support.

20+9

Remove print_jni_name_prefix_on, centralized in os_posix.cpp
Merge illumos-port-14.patch into the main patch to simplify the patch
set.

Tribblix updates mean I'm now using gcc10 rather than gcc7

20+8

Minimal patch noise.

Tidying up.
Remove now unused mutex_scope and cond_scope.
Remove UsePthreads, as it's now the only option.
Clean up set_mutex* and set_cond* now we're exclusively pthreads.

20+7

Remove os::print_statistics()

Remove os_share_solaris.hpp

20+6

SuspendResume is no longer in os::, needs illumos-port-19.patch

os::message_box has been centralized

Removed now unused unpackTime() and compute_Abstime().

20+5

Some big breaking changes here.

In os_posix.cpp, some things like PlatformMutex, PlatformEvent,
PlatformMonitor have dropped the os:: namespace. The definitions have
been centralized, posix uses _event whereas solaris used _Event (like
windows does). And the posix variants all use pthreads, whereas
solaris used native threads, which leads to signature mismatches.

So there are a couple of changes. First, replace mutex_t with
pthread_mutex_t. Second, assign directly rather than setting the
symbols dynamically, which used to be done as a way of switching
between thread-based and lwp-based synchronization.

And with that, in fact, we could use the central posix verions of the
Platform pieces.

And do the same for the cond_ functions as well as the mutex_ functions.

Remove illumos-port-1.patch and roll the pthreads versions in by default

ThreadCrashProtection has moved out of os_posix.{c,h}pp which means we
have to move stuff around.

mutex.hpp, park.hpp, threadCrashProtection.hpp headers reworked
-> illumos-port-18.patch

Remove RecordSynch

20+4

os::infinite_sleep() has been centralised

Build failure in
src/java.base/solaris/classes/sun/nio/fs/SolarisUserDefinedFileAttributeView.java
Looking at the various implementations of this, the solaris one
appears to be old and could simply be updated to use common code like
linux and bsd do.

The file
src/jdk.hotspot.agent/share/classes/sun/jvm/hotspot/debugger/proc/ProcAddress.java
removed getValue(), so use asLongValue() in
src/jdk.hotspot.agent/share/classes/sun/jvm/hotspot/debugger/proc/ProcDebuggerLocal.java

The reproducible builds by default stuff breaks us because it assumes
it will always be enabled and appears not to be. Needs
--with-source-date=current
and also gnu date, so add DATE=/usr/gnu/bin/date to configure

Setting --with-source-date also breaks copyright year generation which
also needs gnu date.

No need to have a Solaris switch to force fork1(), as of S10 that's
the default behaviour.

20+3

Build broken by https://www.illumos.org/issues/14418. That did 2
things -  (1) exposed memcntl and meminfo by default, and (2) changed
the signature for memcntl from caddr_t to void so there's a
mismatch. The fix adopted is to modify the internal java signature for
memcntl to the new version, which still allows builds on older
releases as the old definition in sys/mman.h was effectively invisible
there.

Rename thread_solaris_x86.{c,h}pp -> javaThread_solaris_x86.{c,h}pp
mv thread_solaris_x86.cpp javaThread_solaris_x86.cpp
mv thread_solaris_x86.hpp javaThread_solaris_x86.hpp
sed -i s:_THREAD_:_JAVATHREAD_: javaThread_solaris_x86.hpp
sed -i s:runtime/thread.inline.hpp:runtime/javaThread.hpp:
javaThread_solaris_x86.cpp
and fix up includes in os_solaris.cpp

The checkedNatives stuff now causes compilation failures, so remove it
wholesale.

20+2

Trivial patch noise

20+1

Starting fairly clean

Build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk19 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--enable-deprecated-ports=yes \
--with-source-date=current \
--with-jobs=3 \
DATE=/usr/gnu/bin/date \
STRIP=/usr/gnu/bin/strip

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all
