#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dialog
COMPONENT_VERSION=	1.3
COMPONENT_TIMESTAMP=	20160209
COMPONENT_PROJECT_URL=	http://invisible-island.net/dialog/dialog.html
COMPONENT_SUMMARY=	dialog - display dialog boxes from shell scripts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_TIMESTAMP)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0314f7f2195edc58e7567a024dc1d658c2f8ea732796d8fa4b4927df49803f87
COMPONENT_ARCHIVE_URL=	https://invisible-mirror.net/archives/dialog/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI=		terminal/dialog

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CFLAGS+=	-I/usr/include/ncurses -D_XOPEN_SOURCE_EXTENDED
LDFLAGS+=	-L/usr/gnu/lib -R/usr/gnu/lib -lncurses

CONFIGURE_OPTIONS+=	--enable-included-msgs
CONFIGURE_OPTIONS+=	--enable-nls
CONFIGURE_OPTIONS+=	--enable-widec

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
