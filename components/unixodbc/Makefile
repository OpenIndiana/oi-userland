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
#
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		unixODBC
COMPONENT_VERSION=	2.3.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://unixodbc.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1f5be3edecff9e31072ef738ea1d8019594c4f0c2e3ab427e6eef153491db6a2
COMPONENT_ARCHIVE_URL=	http://ftp.unixodbc.org/pub/unixODBC/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/unixodbc

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

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

PROTOPKGCONFIGDIR32 = $(PROTOUSRLIBDIR)/pkgconfig
PROTOPKGCONFIGDIR64 = $(PROTOUSRLIBDIR64)/pkgconfig

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
	$(MKDIR) $(PROTOPKGCONFIGDIR32)
	$(MKDIR) $(PROTOPKGCONFIGDIR64)
	$(GSED) -e "s#SED_SIZEOF_LONG#4#g" \
	    $(COMPONENT_DIR)/Solaris/unixODBC.pc > \
	    $(PROTOPKGCONFIGDIR32)/unixODBC.pc
	$(GSED) -e "s#SED_SIZEOF_LONG#8#g" \
	    $(COMPONENT_DIR)/Solaris/unixODBC.pc > \
	    $(COMPONENT_DIR)/unixODBC.pc.1
	$(GSED) -e 's#/lib#/lib/$(MACH64)#g' \
	    $(COMPONENT_DIR)/unixODBC.pc.1 > \
	    $(PROTOPKGCONFIGDIR64)/unixODBC.pc
	$(RM) -f $(COMPONENT_DIR)/unixODBC.pc.1

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

