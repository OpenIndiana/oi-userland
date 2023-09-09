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

include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 12.3.0
COMPONENT_SRC= gcc-releases-gcc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/gcc-mirror/gcc/archive/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:f5126461c2b195045471f6934ab067fbf0e10a7e695704208f4a128178cf93af

MPFR_VERSION=4.2.0
MPFR_ARCHIVE_HASH= \
  sha256:691db39178e36fc460c046591e4b0f2a52c8f2b3ee6d750cc2eab25f1eaa999d

MPC_VERSION=1.3.1
MPC_ARCHIVE_HASH= \
  sha256:ab642492f5cf882b74aa0cb730cd410a81edcdbec895183ce930e706c1c759b8

GMP_VERSION=6.2.1
GMP_ARCHIVE_HASH= \
  sha256:eae9326beb4158c386e39a356818031bd28f3124cf915f8c5b1dc4c7a36b4d7c

include $(WS_MAKE_RULES)/gcc-component.mk

CC=/usr/gcc/11/bin/gcc
CXX=/usr/gcc/11/bin/g++

CPPFLAGS+=" -D_TS_ERRNO"
LDFLAGS="-R$OPT/lib"

GCC_MAJOR="$(GCC_COMPONENT_VERSION_MAJOR)"
PKG_VARS += GCC_MAJOR

# Workaround platform definition inconsistency
ifeq ($(strip $(BUILD_BITS)),64)
PARCH = $(MACH:i386=x86_64-pc)
else
PARCH = $(MACH:i386=i386-pc)
endif
GNU_TRIPLET = $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)
PKG_MACROS += GNU_TRIPLET="$(GNU_TRIPLET)"

COMPONENT_PRE_CONFIGURE_ACTION += \
	cd $(SOURCE_DIR) && autogen Makefile.def

CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 = $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS+= --with-ld=$(LD) --without-gnu-ld
CONFIGURE_OPTIONS+= --with-as=/usr/bin/gas --with-gnu-as
CONFIGURE_OPTIONS+= --with-build-time-tools=/usr/gnu/${TRIPLETS[amd64]}/bin
CONFIGURE_OPTIONS+= --with-build-config=no
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,go,objc
# CONFIGURE_OPTIONS+= --with-arch-32=i586
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --with-system-zlib
CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-__cxa_atexit
CONFIGURE_OPTIONS+= --enable-initfini-array
# CONFIGURE_OPTIONS+= --disable-libitm
CONFIGURE_OPTIONS+= --with-diagnostics-urls=auto-if-env
CONFIGURE_OPTIONS+= enable_frame_pointer=yes

COMPONENT_TEST_ENV += LC_ALL=C.UTF-8

PKG_HARDLINKS += usr/gcc/12/bin/g++
PKG_HARDLINKS += usr/gcc/12/bin/gcc
PKG_HARDLINKS += usr/gcc/12/bin/gcc-ar
PKG_HARDLINKS += usr/gcc/12/bin/gcc-nm
PKG_HARDLINKS += usr/gcc/12/bin/gcc-ranlib
PKG_HARDLINKS += usr/gcc/12/bin/gccgo
PKG_HARDLINKS += usr/gcc/12/bin/gfortran

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
