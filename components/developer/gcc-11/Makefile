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
# Copyright 2013 Andrzej Szeszo.  All rights reserved.
# Copyright 2016-2019 Aurelien Larcher. All rights reserved.
# Copyright 2021 Andreas Wacknitz. All rights reserved.
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 11.5.0
COMPONENT_SRC= gcc-releases-gcc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/gcc-mirror/gcc/archive/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:ab1a9172b03f552f2a6277d1316ad91b0b025e72ef1837859b0121d85a89d51a

MPFR_VERSION=4.2.1
MPFR_ARCHIVE_HASH=	sha256:b9df93635b20e4089c29623b19420c4ac848a1b29df1cfd59f26cab0d2666aa0

MPC_VERSION=1.3.1
MPC_ARCHIVE_HASH=	sha256:ab642492f5cf882b74aa0cb730cd410a81edcdbec895183ce930e706c1c759b8

GMP_VERSION=6.3.0
GMP_ARCHIVE_HASH=	sha256:ac28211a7cfb609bae2e2c8d6058d66c8fe96434f740cf6fe2e47b000d1c20cb

include $(WS_MAKE_RULES)/gcc-component.mk

GCC_MAJOR="$(GCC_COMPONENT_VERSION_MAJOR)"
PKG_VARS += GCC_MAJOR

# Workaround platform definition inconsistency
ifeq ($(strip $(BUILD_BITS)),64)
PARCH = $(MACH:i386=x86_64-pc)
else
PARCH = $(MACH:i386=i386-pc)
endif
GNU_TRIPLET = $(PARCH:sparc=sparcv9-sun)-solaris$(SOLARIS_VERSION)
PKG_MACROS += GNU_TRIPLET="$(GNU_TRIPLET)"

CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 = $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS += --with-diagnostics-urls=auto-if-env
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-objc-gc
CONFIGURE_OPTIONS += --disable-libitm
CONFIGURE_OPTIONS.sparc += --with-mulhigh-size=2048
CONFIGURE_OPTIONS.sparc += --with-cpu=ultrasparc
CONFIGURE_OPTIONS.sparc += --enable-link-mutex
CONFIGURE_OPTIONS += --enable-initfini-array
CONFIGURE_OPTIONS += --enable-__cxa_atexit
CONFIGURE_OPTIONS += --enable-languages=c,c++,fortran,go,lto,objc
CONFIGURE_OPTIONS += enable_frame_pointer=yes

# Master test results are different between amd64 and SPARCV9.
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH64).master

PKG_HARDLINKS += usr/gcc/11/bin/g++
PKG_HARDLINKS += usr/gcc/11/bin/gcc
PKG_HARDLINKS += usr/gcc/11/bin/gcc-ar
PKG_HARDLINKS += usr/gcc/11/bin/gcc-nm
PKG_HARDLINKS += usr/gcc/11/bin/gcc-ranlib
PKG_HARDLINKS += usr/gcc/11/bin/gccgo
PKG_HARDLINKS += usr/gcc/11/bin/gfortran

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += developer/linker
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/header
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c-runtime
REQUIRED_PACKAGES += system/library/math
