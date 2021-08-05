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
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 10.3.0
COMPONENT_SRC= gcc-releases-gcc-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/gcc-mirror/gcc/archive/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:6e2622af6c2b1640bd2a66458cf979b4d848a3b0f7d7896a322befe51c933c9f

MPFR_VERSION=4.1.0
MPFR_ARCHIVE_HASH= \
  sha256:feced2d430dd5a97805fa289fed3fc8ff2b094c02d05287fd6133e7f1f0ec926

MPC_VERSION=1.2.1
MPC_ARCHIVE_HASH= \
  sha256:17503d2c395dfcf106b622dc142683c1199431d095367c6aacba6eec30340459

GMP_VERSION=6.2.1
GMP_ARCHIVE_HASH= \
  sha256:eae9326beb4158c386e39a356818031bd28f3124cf915f8c5b1dc4c7a36b4d7c

include $(WS_MAKE_RULES)/gcc-component.mk

PYTHON_VERSION= 3.9

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

CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 = $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS+= --with-diagnostics-urls=auto-if-env
CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-objc-gc
CONFIGURE_OPTIONS.i386+= --enable-initfini-array
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,lto,objc
CONFIGURE_OPTIONS+= --disable-libitm
CONFIGURE_OPTIONS+= enable_frame_pointer=yes

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/gc
