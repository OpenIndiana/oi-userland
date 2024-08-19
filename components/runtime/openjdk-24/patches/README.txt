 This is originally derived from the pkgsrc-joyent set for openjdk11,
considerably modified. Cut from the jdk15 patches as of jdk15+32.

See also README-zero.txt for note on a project zero variant.

JDK 24 now that jdk23 has been branched off.

24+9, 24+10, 24+11

Trivial patch noise.

24+8

In os_solaris.cpp, os::pd_free_memory() has been removed and
os::pd_disclaim_memory() added. Looking at AIX, both were no-ops. On
Linux, they're quite different. On BSD, the implementation is
identical. So what I'll do is keep the same implementation, just
changing the name and signature.

24+7

No changes.

Cleanup: Removed last remnants of extended_FILE_stdio, it's unused as 32-bit
only, and the code to enable it had already been removed.

24+6

No changes.

24+5

Trivial patch noise.

24+4

Offsets due to os::committed_in_range() implementation. The guards
are plain wrong, so needed to correct them in illumos-port-28.patch

24+3

Wants an os::rss() implementation; return 0 for now, just like AIX does
(and other platforms return 0 as the "don't know" answer).

24+2

Trivial patch noise.

24+0, 24+1

Start with no changes from 23+26.

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
