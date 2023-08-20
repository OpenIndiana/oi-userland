This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for note on a project zero variant.

JDK 22 now that jdk21 has been forked off.

Issues known that indicate serious bugs, likely due to not integrating
loom correctly as they date back to that change. Specifically, I
suspect we need to provide a working DefaultPoller implementation
rather than the current stub.
* jshell doesn't work
* illuminate doesn't work

22+11

Remove AttachListener::pd_find_operation()
Merge and delete tribblix-attachListener_solaris.patch

22+9, 22+10

Trivial patch noise.

22+8

Fix zero port; see Atomic and print_register_info change in jdk 21+23

Needed to add stubs for can_trim_native_heap() and trim_native_heap()
to os_solaris.inline.hpp

22+7

Trivial patch noise.

22+6

Trivial patch noise.
Dropped the old make/autoconf/lib-freetype.m4 patch, as it's
not relevant to us.
Fix format warning in print_memory_info()

22+4, 22+5

Trivial patch noise.

22+3

Minor patch noise.

22+2

Some patch noise, especially Awt2dLibraries.gmk and static linking.

22+1

No changes needed, identical to 21+26.

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
