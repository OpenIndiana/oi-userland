"Zero is a port of OpenJDK that uses no assembler and therefore can
trivially be built on any system."

https://openjdk.org/projects/zero/

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

These are current and tested for a successful build (not necessarily
fully working) as of jdk 26+19. They don't provide a proper zero port,
as they still have assembler that needs to be removed. But this
provides a starting point.

There's a warning:

OpenJDK 64-Bit Zero VM warning: Unsupported locking mode for this CPU.

which you can get around by passing -XX:LockingMode=0 or -XX:LockingMode=1

The two patches above are now applied by default, so we at least catch
any source incompatibilities early.

Configure:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin bash ./configure \
--enable-unlimited-crypto --with-boot-jdk=/usr/jdk/instances/jdk24 \
--with-native-debug-symbols=none \
--with-toolchain-type=gcc \
--disable-dtrace \
--disable-warnings-as-errors \
--enable-jvm-feature-zero --with-jvm-variants=zero \
--with-source-date=current \
--with-jobs=4 \
DATE=/usr/gnu/bin/date \
LOCALE=/bin/true \
STRIP=/usr/gnu/bin/strip

build:

env PATH=/usr/bin:/usr/sbin:/usr/sfw/bin:/usr/gnu/bin gmake product-images CONF=solaris-x86_64-zero-release
