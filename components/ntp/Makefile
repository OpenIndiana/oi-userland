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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ntp-dev
COMPONENT_PATCH_VERSION=	200
COMPONENT_VERSION=	4.2.5
HUMAN_VERSION=		$(COMPONENT_VERSION)p$(COMPONENT_PATCH_VERSION)
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_PATCH_VERSION)
COMPONENT_PROJECT_URL=	http://www.ntp.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:97eeb4e90fba1ae3210e13574a4b3df715957cb9895264c6a455ee97dec87611
COMPONENT_ARCHIVE_URL=	http://archive.ntp.org/ntp4/ntp-dev/$(COMPONENT_ARCHIVE)
PATCH_LEVEL = 0

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS +=	$(studio_C99_ENABLE) -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--bindir=/usr/sbin
CONFIGURE_OPTIONS +=	--with-binsubdir=sbin
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/inet
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/inet
CONFIGURE_OPTIONS +=	--enable-all-clocks
CONFIGURE_OPTIONS +=	--enable-debugging
CONFIGURE_OPTIONS +=	--enable-debug-timing
CONFIGURE_OPTIONS +=	--disable-optional-args
CONFIGURE_OPTIONS +=	--enable-parse-clocks
CONFIGURE_OPTIONS +=	--enable-ignore-dns-errors
CONFIGURE_OPTIONS +=	--without-ntpsnmpd
CONFIGURE_OPTIONS +=	--without-lineeditlibs
CONFIGURE_OPTIONS +=	--with-openssl-libdir=/lib
CONFIGURE_OPTIONS +=	--disable-getifaddrs

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

build:		$(BUILD_32)
install:	$(INSTALL_32)
test:		$(NO_TESTS)

include ../../make-rules/depend.mk
