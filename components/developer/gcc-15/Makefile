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
BOOTSTRAP_COMPONENT= no
include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 15.3.0
COMPONENT_SRC= gcc-releases-gcc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/gcc-mirror/gcc/archive/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:f910401fce14ed9189e0f1efbbed06cb4032102c6b0c8d0b5d0a844c9c1c396f
COMPONENT_BOOTSTRAP= yes

MPFR_VERSION= 4.2.1
MPFR_ARCHIVE_HASH= sha256:b9df93635b20e4089c29623b19420c4ac848a1b29df1cfd59f26cab0d2666aa0

MPC_VERSION= 1.3.1
MPC_ARCHIVE_HASH= sha256:ab642492f5cf882b74aa0cb730cd410a81edcdbec895183ce930e706c1c759b8

GMP_VERSION= 6.3.0
GMP_ARCHIVE_HASH= sha256:ac28211a7cfb609bae2e2c8d6058d66c8fe96434f740cf6fe2e47b000d1c20cb

include $(WS_MAKE_RULES)/gcc-component.mk

ifeq ($(COMPONENT_BOOTSTRAP),yes)
CC=/usr/gcc/14/bin/gcc
CXX=/usr/gcc/14/bin/g++
else
CC=/usr/gcc/$(GCC_MAJOR)/bin/gcc
CXX=/usr/gcc/$(GCC_MAJOR)/bin/g++
endif

# Use gcc's default flags
CFLAGS=
CPPFLAGS=
CXXFLAGS=

CPPFLAGS += " -D_TS_ERRNO"
LDFLAGS= "-R$OPT/lib"

GCC_MAJOR= $(GCC_COMPONENT_VERSION_MAJOR)
PKG_VARS += GCC_MAJOR
PKG_MACROS +=   GCC_MAJOR_VERSION=$(GCC_MAJOR)
PKG_MACROS +=   GCC_VERSION=15
PKG_MACROS +=	GCCVER=15
PKG_MACROS +=   GCC_BASEDIR=usr/gcc/$(GCC_MAJOR)

# Workaround platform definition inconsistency
PARCH= $(MACH:i386=x86_64-pc)

GNU_TRIPLET= $(PARCH)-solaris$(SOLARIS_VERSION)
PKG_MACROS += GNU_TRIPLET="$(GNU_TRIPLET)"

COMPONENT_PRE_CONFIGURE_ACTION += \
	cd $(SOURCE_DIR) && autogen Makefile.def

CONFIGURE_BINDIR.64= $(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64= $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS += --with-ld=$(LD) --without-gnu-ld
CONFIGURE_OPTIONS += --with-as=/usr/bin/gas --with-gnu-as
CONFIGURE_OPTIONS += --with-build-time-tools=/usr/gnu/${TRIPLETS[amd64]}/bin
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

COMPONENT_TEST_TRANSFORMS= -n \
	"-e '/Running/p' " \
	"-e '/Summary/p' " \
	"-e '/\# of/p' "

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
