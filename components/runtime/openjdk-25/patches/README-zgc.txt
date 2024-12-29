The marketing blurb:

The Z Garbage Collector (ZGC) is a scalable low latency garbage
collector. ZGC performs all expensive work concurrently, without
stopping the execution of application threads for more than a
millisecond. It is suitable for applications which require low
latency. Pause times are independent of the heap size that is being
used. ZGC works well with heap sizes from a few hundred megabytes to
16TB.

It's not available on Solaris/illumos by default, but there's an
experimental patch here that will enable it. To do that, go to the
root of the source tree after unpacking and applying all the other
patches, and apply with

gpatch -p1 < .../illumos-zgc.patch

This patch does 2 things:

1. Patches make/autoconf/jvm-features.m4 to add solaris (just x86) to
the platforms that zgc will be built on.

2. Adds a basic implementation of support for zgc under the
src/hotspot/os/solaris/gc directory.

The support files are a mishmash of the bsd and linux
implementations. Mostly the simple bsd skeleton, with mmap() instead
of the bsd mremap(), using MAP_ANONYMOUS to simply get an anonymous
mapping.

It can be enabled via the flag

java -XX:+UseZGC ...

Initial testing indicates that it does work, although some crashes
have been seen.
