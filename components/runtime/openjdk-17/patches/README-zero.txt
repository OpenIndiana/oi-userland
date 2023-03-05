"Zero is a port of OpenJDK that uses no assembler and therefore can
trivially be built on any system."

https://openjdk.java.net/projects/zero/

The idea here is to potentially have an illumos port of zero. It's not
so interesting on x86, for which we have a proper port anyway, but if
we can get zero to work on x86 then it should be possible to get it to
work on sparc too.

It still needs the basic solaris patchset. It's designed more to support
new hardware architectures (hence the zero assembler) than as a way to
do an OS port.

There are 2 patches:

illumos-zero-1.patch
Fixes src/hotspot/cpu/zero/stubGenerator_zero.cpp

illumos-zero-2.patch
Adds the src/hotspot/os_cpu/solaris_zero directory and contents

These are current and tested for jdk 17+26. They don't provide a
proper zero port, as they still have x86 assembler that needs to be
removed.

cd to the jdk source that has the other patches applied and

gpatch -p1 < ${THOME}/build/patches/openjdk17/illumos-zero-1.patch
gpatch -p1 < ${THOME}/build/patches/openjdk17/illumos-zero-2.patch

Configure:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk16 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--enable-deprecated-ports=yes \
--enable-jvm-feature-zero --with-jvm-variants=zero \
--with-jobs=3

build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake all CONF=solaris-x86_64-zero-release
