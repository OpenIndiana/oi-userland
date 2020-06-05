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
# Copyright 2016 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		notion-3
COMPONENT_VERSION=	2015061300
COMPONENT_PROJECT_URL=	http://notion.sf.net
COMPONENT_FMRI=		desktop/window-manager/notion-3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	3-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3c9d9f35a9fb0d17c263b76fe28f7a1a4a05b7d6140545524cc1effd98c5c305
COMPONENT_ARCHIVE_URL=	https://github.com/raboof/notion/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Modified LGPL
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Notion 3 window manager
COMPONENT_CLASSIFICATION=System/X11

include ../../../make-rules/prep.mk
include ../../../make-rules/justmake.mk
include ../../../make-rules/ips.mk

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += ETCDIR=/etc/notion

COMPONENT_INSTALL_ENV += ETCDIR=/etc/notion

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr

# notion uses xmessage to display errors at run time
REQUIRED_PACKAGES += x11/xmessage
