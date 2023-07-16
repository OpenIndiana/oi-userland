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

include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 11.4.0
COMPONENT_REVISION= 1
COMPONENT_SRC= gcc-releases-gcc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/gcc-mirror/gcc/archive/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:aab0f644ae9dc169c80fb2fe0f63baf4d9b147a1db4bdbcba3ec530afcb6a601

MPFR_VERSION=4.2.0
MPFR_ARCHIVE_HASH=	sha256:691db39178e36fc460c046591e4b0f2a52c8f2b3ee6d750cc2eab25f1eaa999d

MPC_VERSION=1.3.1
MPC_ARCHIVE_HASH=	sha256:ab642492f5cf882b74aa0cb730cd410a81edcdbec895183ce930e706c1c759b8

GMP_VERSION=6.2.1
GMP_ARCHIVE_HASH=	sha256:eae9326beb4158c386e39a356818031bd28f3124cf915f8c5b1dc4c7a36b4d7c

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

CONFIGURE_OPTIONS+= --with-diagnostics-urls=auto-if-env
CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-objc-gc
CONFIGURE_OPTIONS.i386+= --disable-libitm
CONFIGURE_OPTIONS.sparc+= --with-mulhigh-size=2048
CONFIGURE_OPTIONS.sparc+= --with-cpu=ultrasparc
CONFIGURE_OPTIONS.sparc+= --enable-link-mutex
CONFIGURE_OPTIONS+= --enable-initfini-array
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,go,lto,objc
CONFIGURE_OPTIONS+= enable_frame_pointer=yes

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
