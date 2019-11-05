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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, Andreas Wacknitz
# Copyright (c) 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

PATH=$(PATH.illumos)

COMPONENT_NAME=		unixODBC
COMPONENT_VERSION=	2.3.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.unixodbc.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:45f169ba1f454a72b8fcbb82abd832630a3bf93baa84731cf2949f449e1e3e77
COMPONENT_ARCHIVE_URL=	ftp://ftp.unixodbc.org/pub/unixODBC/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/unixodbc

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += -std=c99

GSED = /usr/gnu/bin/sed

X11LIB.32 = $(CONFIGURE_PREFIX)/lib
X11LIB.64 = $(CONFIGURE_PREFIX)/lib/$(MACH64)

PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig
PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig

LD_OPTIONS += -lsocket -lresolv -lnsl -lgen

CONFIGURE_OPTIONS  +=	--includedir=$(CONFIGURE_PREFIX)/include/odbc
CONFIGURE_OPTIONS  +=	--localstatedir=/var
CONFIGURE_OPTIONS  +=	--sysconfdir=/etc/odbc
CONFIGURE_OPTIONS  +=	--x-includes="$(CONFIGURE_PREFIX)/include"
CONFIGURE_OPTIONS  +=	--x-libraries="$(X11LIB.$(BITS))"
CONFIGURE_OPTIONS  +=	--enable-shared
CONFIGURE_OPTIONS  +=	--disable-static
CONFIGURE_OPTIONS  +=	--disable-libtool-lock
CONFIGURE_OPTIONS  +=	--disable-gui
CONFIGURE_OPTIONS  +=	--enable-threads
CONFIGURE_OPTIONS  +=	--disable-gnuthreads
CONFIGURE_OPTIONS  +=	--enable-readline
CONFIGURE_OPTIONS  +=	--enable-inicaching
CONFIGURE_OPTIONS  +=	--enable-drivers=yes
CONFIGURE_OPTIONS  +=	--enable-driver-conf=yes
CONFIGURE_OPTIONS  +=	--enable-fdb
CONFIGURE_OPTIONS  +=	--enable-odbctrace
CONFIGURE_OPTIONS  +=	--enable-iconv
CONFIGURE_OPTIONS  +=	--enable-stats
CONFIGURE_OPTIONS  +=	--enable-rtldgroup
CONFIGURE_OPTIONS  +=	--disable-ltdllib
CONFIGURE_OPTIONS  +=	--without-pth
CONFIGURE_OPTIONS  +=	--without-pth-test
CONFIGURE_OPTIONS  +=	--with-libiconv-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=	--disable-ltdl-install
CONFIGURE_OPTIONS  +=	--with-pic

CONFIGURE_ENV  +=   LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV  +=   INSTALL="$(INSTALL)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
