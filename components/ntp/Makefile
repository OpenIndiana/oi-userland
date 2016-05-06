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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ntp
COMPONENT_VERSION=	4.2.8
COMPONENT_PATCH_VERSION=	6
COMPONENT_RC_VERSION=	1
HUMAN_VERSION=		$(COMPONENT_VERSION)p$(COMPONENT_PATCH_VERSION)
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_PATCH_VERSION)
COMPONENT_PROJECT_URL=	http://www.ntp.org/
COMPONENT_SRC_NAME=	ntp
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE_HASH=	 \
    sha256:583d0e1c573ace30a9c6afbea0fc52cae9c8c916dbc15c026e485a0dda4ba048
COMPONENT_ARCHIVE_URL=	http://archive.ntp.org/ntp4/ntp-4.2/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB= service/ntp

TPNO=			20866

PATCH_LEVEL = 0

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS +=	 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

studio_C99MODE= $(studio_C99_ENABLE)
CFLAGS.studio.i386 =	-preserve_argvalues=complete

CONFIGURE_BINDIR.64 = $(USRSBINDIR)

CONFIGURE_OPTIONS +=	--with-binsubdir=sbin
CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBDIR)/inet
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/inet
CONFIGURE_OPTIONS +=	--enable-all-clocks
CONFIGURE_OPTIONS +=	--enable-debugging
CONFIGURE_OPTIONS +=	--enable-debug-timing
CONFIGURE_OPTIONS +=	--disable-optional-args
CONFIGURE_OPTIONS +=	--enable-parse-clocks
CONFIGURE_OPTIONS +=	--enable-ignore-dns-errors
CONFIGURE_OPTIONS +=	--without-ntpsnmpd
CONFIGURE_OPTIONS +=	--with-openssl-libdir=$(LIBDIR)/$(MACH64)

REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/crypto
