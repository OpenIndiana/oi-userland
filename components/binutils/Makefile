#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
# At the moment, we build both 32-bit and 64-bit versions of binutils, but only
# deliver the 32-bit binaries and libraries.
BUILD_BITS= 32_and_64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		binutils
COMPONENT_VERSION=	2.25.1
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:b5b14added7d78a8d1ca70b5cb75fef57ce2197264f4f5835326b0df22ac9f22
COMPONENT_BUGDB=	utility/gnu-binutils

TPNO=			23923

TEST_TARGET= $(TEST_32)
include $(WS_MAKE_RULES)/gnu-component.mk

PATCH_LEVEL := 0

PARCH =		$(MACH:i386=i386-pc)
GNU_ARCH =	$(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=	GNU_ARCH="$(GNU_ARCH)"

CFLAGS.i386 = -mtune=opteron -march=opteron
CFLAGS.sparc = -mtune=ultrasparc3 -mcpu=ultrasparc3 -mvis2 \
  -mno-unaligned-doubles -mhard-float -mimpure-text

CFLAGS = $(CC_BITS) -g -O2 -std=c99
CFLAGS += $(CFLAGS.$(MACH))
CFLAGS += -D_REENTRANT  $(CPP_LARGEFILES) $(CPP_POSIX)
CXXFLAGS = $(CC_BITS) -g -O2 -std=c++03
CXXFLAGS += $(CFLAGS.$(MACH))
CXXFLAGS += -D_REENTRANT $(CPP_LARGEFILES) $(CPP_POSIX)
CPPFLAGS += -D_REENTRANT $(CPP_LARGEFILES) $(CPP_POSIX)

CONFIGURE_PREFIX =	$(USRDIR)/gnu

CONFIGURE_ENV +=	LD_OPTIONS="$(LD_OPTIONS)"
CONFIGURE_ENV +=	CCLD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV +=	LIBS="$(LIBS)"
CONFIGURE_ENV +=	PATH="$(PATH)"

CONFIGURE_OPTIONS +=	--mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=    --disable-gold
CONFIGURE_OPTIONS +=    --disable-libtool-lock
CONFIGURE_OPTIONS +=	--enable-64-bit-bfd
CONFIGURE_OPTIONS +=    --enable-deterministic-archives
CONFIGURE_OPTIONS +=    --enable-host-shared
CONFIGURE_OPTIONS +=    --enable-largefile
CONFIGURE_OPTIONS +=    --enable-nls
CONFIGURE_OPTIONS +=    --enable-plugins

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/flex-runtime
