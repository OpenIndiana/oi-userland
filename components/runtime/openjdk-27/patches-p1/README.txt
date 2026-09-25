JDK 27 now that jdk26 has been branched off.

27+35

No changes; first release candidate.

Cleanup: defaultPath() no longer includes SUNWspro.

27+26, 27+27, 27+28, 27+29, 27+30, 27+31, 27+32, 27+33, 27+34

No changes.

27+25

Minor patch noise.

27+24

Minor patch noise, associated with the JVMCI removal.

27+20, 27+21, 27+22, 27+23

No changes.

27+19

FREE_C_HEAP_ARRAY has lost its first argument.

27+18

Minor patch noise.

27+17

No changes.

27+16

For ProcessImpl, VFORK has been removed.

Boot jdk bumped to jdk26.

27+15

Trivial patch noise.

27+14

Added a no-op implementation of print_open_file_descriptors()

27+12, 27+13

Trivial patch noise.

27+11

Functions release_memory_special() pd_release_memory_special() have
been removed.

27+10

os::remove_stack_guard_pages() now returns void not bool

27+9

PollerProvider rework. This may need to be redone; I've taken the
simplistic implementation from aix, which isn't specialised for
virtual threads.

27+8

Trivial patch noise.

27+7

Rework of libjaas, drop hunk entirely.

27+6

Changes for the shuffling associated with containerization and the
os::Machine class.

27+5

Need to remove includes of runtime/prefetch.hpp

Cleanup: Fix AtomicAccess so tests build.

27+4

Trivial patch noise.

27+3

Minor patch noise.

27+2

Cleanup: errno alignment with 8366272

27+1

No changes.

27+0

Start with no changes from 26+27. (Still reports as 26.)

Patch cleanup, merged all the flags-ldflags patch hunks into a single
file, and all patches now -p1.

Build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk26 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-warnings-as-errors \
--with-source-date=current \
--with-jobs=4 \
DATE=/usr/gnu/bin/date \
LOCALE=/bin/true \
STRIP=/usr/gnu/bin/strip

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake product-images
