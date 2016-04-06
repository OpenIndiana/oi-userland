#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		notion-3
COMPONENT_VERSION=	2014052800
COMPONENT_PROJECT_URL=	http://notion.sf.net
COMPONENT_FMRI=		desktop/window-manager/notion-3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:3619c90fb1f4b49cbddbfa8b94aa1d1e7e5a7e933764aea3ab3b25c6ef3c7027
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/notion/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Modified LGPL
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Notion 3 window manager

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += ETCDIR=/etc/notion

COMPONENT_INSTALL_ENV += ETCDIR=/etc/notion

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
