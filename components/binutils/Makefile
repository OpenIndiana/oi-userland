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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		binutils
COMPONENT_VERSION=	2.27
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:369737ce51587f92466041a97ab7d2358c6d9e1b6490b3940eb09fb0a9a6ac88
COMPONENT_BUGDB=	utility/gnu-binutils
COMPONENT_ANITYA_ID=	7981

TPNO=			32076

TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

export PATH=$(dirname $(CC)):$(GNUBIN):/usr/bin
COMPONENT_TEST_ARGS += -k
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

COMPONENT_TEST_TRANSFORMS += '-e "/bin\/gcc/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/bin\/g++/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Test Run By /d" '

PARCH =		$(MACH:i386=x86_64-pc)
GNU_ARCH =	$(PARCH:sparc=sparcv9-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=	GNU_ARCH="$(GNU_ARCH)"

CONFIGURE_PREFIX =	$(USRDIR)/gnu

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
CONFIGURE_OPTIONS +=    --with-system-zlib
CONFIGURE_OPTIONS +=    --build=$(GNU_ARCH)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/flex-runtime
