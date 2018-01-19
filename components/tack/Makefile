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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tack
COMPONENT_VERSION=	1.07
IPS_COMPONENT_VERSION=	1.0.7
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/ncurses/
COMPONENT_SUMMARY=	A CRT screen handling and optimization package
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e7ce787d1f7c63e51781eca9ebf4c349fcf4cbecb78cf37d60754f4c122c87fe
COMPONENT_ARCHIVE_URL=	ftp://ftp.invisible-island.net/ncurses/tack-1.07.tgz
COMPONENT_FMRI=		terminal/tack
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX = /usr/gnu

CFLAGS += -I/usr/include/ncurses

CONFIGURE_OPTIONS +=	--enable-widec

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
