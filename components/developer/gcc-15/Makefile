#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 15.3.0
COMPONENT_REVISION= 2
COMPONENT_ARCHIVE_HASH= sha256:fa59c1beef8995f27c4d71c1df227587189315d3e6faff1bb4306e61b0c530eb

MPFR_VERSION= 4.2.2
MPC_VERSION= 1.4.1
GMP_VERSION= 6.3.0

# This is the GCC version used to build this GCC.
#
# When we bootstrap, we need to build using the current default GCC (see
# GCC_DEFAULT in shared-macros.mk) and so the GCC_VERSION setting here is
# commented out.  Once this component is packaged, we can skip the bootstrap by
# setting the GCC_VERSION to our major version (and so the GCC_VERSION setting
# here should be uncommented).
GCC_VERSION = 15

include $(WS_MAKE_RULES)/gcc-component.mk

LDFLAGS= "-R$OPT/lib"

GCC_MAJOR= $(GCC_COMPONENT_VERSION_MAJOR)
PKG_MACROS += GCCVER=$(GCC_MAJOR)

COMPONENT_PRE_CONFIGURE_ACTION += \
	cd $(SOURCE_DIR) && /usr/bin/autogen Makefile.def

CONFIGURE_BINDIR.64= $(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64= $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS += --with-build-config=no
CONFIGURE_OPTIONS += --enable-languages=c,c++,fortran,go,objc
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-system-zlib
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-__cxa_atexit
CONFIGURE_OPTIONS += --enable-initfini-array
CONFIGURE_OPTIONS += --enable-clocale=dragonfly
CONFIGURE_OPTIONS += --with-diagnostics-urls=auto-if-env
CONFIGURE_OPTIONS += enable_frame_pointer=yes

COMPONENT_TEST_ENV += LC_ALL=C.UTF-8

PKG_HARDLINKS += usr/gcc/$(GCC_MAJOR)/bin/g++
PKG_HARDLINKS += usr/gcc/$(GCC_MAJOR)/bin/gcc
PKG_HARDLINKS += usr/gcc/$(GCC_MAJOR)/bin/gcc-ar
PKG_HARDLINKS += usr/gcc/$(GCC_MAJOR)/bin/gcc-nm
PKG_HARDLINKS += usr/gcc/$(GCC_MAJOR)/bin/gcc-ranlib
PKG_HARDLINKS += usr/gcc/$(GCC_MAJOR)/bin/gccgo
PKG_HARDLINKS += usr/gcc/$(GCC_MAJOR)/bin/gfortran

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += developer/linker
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c-runtime
REQUIRED_PACKAGES += system/library/math
