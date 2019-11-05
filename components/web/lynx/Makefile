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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lynx
COMPONENT_VERSION=	2.8.9rel.1
IPS_COMPONENT_VERSION=	2.8.9
COMPONENT_FMRI=		web/browser/lynx
COMPONENT_SUMMARY=	Text-mode web browser
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_PROJECT_URL=	https://lynx.invisible-island.net/
COMPONENT_SRC=		$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:387f193d7792f9cfada14c60b0e5c0bff18f227d9257a39483e14fa1aaf79595
COMPONENT_ARCHIVE_URL=	http://invisible-mirror.net/archives/$(COMPONENT_NAME)/tarballs/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed to successfully find lynx.pot.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS +=	-std=c99 -D_XOPEN_SOURCE=600
CFLAGS +=	-I/usr/include/ncurses
CFLAGS +=	-I/usr/include/openssl

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--enable-nls
CONFIGURE_OPTIONS +=	--enable-japanese-utf8
CONFIGURE_OPTIONS +=	--enable-widec
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/lynx
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-screen=ncurses

# Use the HTML and CSS styling external test suite as referenced at
# http://www.w3.org/2005/MWI/Tests/
COMPONENT_TEST_CMD = $(@D)/src/lynx
COMPONENT_TEST_ARGS = -dump \
	http://web.archive.org/web/20160629092744/http://cameronmoll.com/mobile/mkp/pg1.html \
	http://web.archive.org/web/20160629092744/http://cameronmoll.com/mobile/mkp/pg2.html \
	http://web.archive.org/web/20160629092744/http://cameronmoll.com/mobile/mkp/pg3.html \
	http://web.archive.org/web/20160629092744/http://cameronmoll.com/mobile/mkp/pg4.html
COMPONENT_TEST_TARGETS =

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

# lynx should be installed before running tests
test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
