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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

CONFIGURE_DEFAULT_DIRS= pre-2.60
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lynx
COMPONENT_VERSION=	2.9.3
COMPONENT_SUMMARY=	Text-mode web browser
COMPONENT_PROJECT_URL=	https://lynx.invisible-island.net/
COMPONENT_SRC=		$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:174b7f2866a60f3247ba75f5c7dbb10b124aede4a1359312de15f3bfebd2050f
COMPONENT_ARCHIVE_URL=	http://invisible-mirror.net/archives/$(COMPONENT_NAME)/tarballs/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		web/browser/lynx
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

# Needed to successfully find lynx.pot.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS +=	-std=c99 $(XPG6)
CFLAGS +=	-I/usr/include/ncurses
CFLAGS +=	-I$(OPENSSL_INCDIR)

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--enable-nls
CONFIGURE_OPTIONS +=	--enable-japanese-utf8
CONFIGURE_OPTIONS +=	--enable-widec
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/lynx
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-screen=ncurses

# lynx should be installed before running tests
#
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

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
