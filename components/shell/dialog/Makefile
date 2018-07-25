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
# Copyright 2018 Michal Nowak
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dialog
COMPONENT_VERSION=	1.3
COMPONENT_TIMESTAMP=	20180621
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://invisible-island.net/dialog/dialog.html
COMPONENT_SUMMARY=	dialog - display dialog boxes from shell scripts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_TIMESTAMP)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4a4859e2b22d24e46c1a529b5a5605b95503aa04da4432f7bbd713e3e867587a
COMPONENT_ARCHIVE_URL=	https://invisible-mirror.net/archives/dialog/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	https://invisible-mirror.net/archives/dialog/$(COMPONENT_ARCHIVE).asc
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

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
