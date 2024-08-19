To enable the ffi fallback for the foreign linker:

--enable-fallback-linker

That works, but adds FFI to the dependencies. To bundle the FFI we
use, you need to

--enable-libffi-bundling

and then help the build out so it can find the right file. The search
logic (see make/autoconf/lib-ffi.m4) is a bit of guesswork and
linux-specific.

You can't use a simple --with-libffi=/usr, because it doesn't know
where our 64-bit library is. So you have to be more specific:

--with-libffi-include=/usr/include
--with-libffi-lib=/usr/lib/amd64

(You don't need the first one, as that's already the default.)

That still doesn't quite work, as we have multiple libffi.so.X files
(for backwards compatibility) which causes confusion:

checking for libffi lib file location... /var/tmp/ud/jdk21-jdk-21-28/build/.configure-support/generated-configure.sh: line 144232: test: too many arguments
configure: error: Could not locate libffi.so.? for bundling in /usr/lib/amd64

So I think the way to avoid that would be to create a temporary
directory and structure that in a way the configure script expects.
