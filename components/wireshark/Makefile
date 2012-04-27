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

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	1.6.5
COMPONENT_PROJECT_URL=	http://www.wireshark.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:151768199f9b50f5593b97025a33303df4d3b3983a203be89d8a1f5ba830bfcd
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

CONFIGURE_OPTIONS +=	--bindir=/usr/sbin
CONFIGURE_OPTIONS +=	--disable-usr-local
CONFIGURE_OPTIONS +=	--disable-randpkt
CONFIGURE_OPTIONS +=	--disable-dftest
CONFIGURE_OPTIONS +=	--disable-idl2wrs
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 
CONFIGURE_OPTIONS +=	PATH="/usr/perl5/bin:/usr/gnu/bin:$(PATH)"

# We need to avoid RPATH=/usr/lib in Wireshark libraries so that we can
# create successfully IPS package of different Wireshark branch than is
# installed on build system without dependency errors.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e 's,-L/usr/lib -R/usr/lib,,' -e 's,-R/usr/lib,,' \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
