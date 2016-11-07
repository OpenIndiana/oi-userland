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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mrxvt
COMPONENT_VERSION=	0.5.4
COMPONENT_PROJECT_URL=	http://materm.sourceforge.net/wiki/pmwiki.php
COMPONENT_SUMMARY=	Mrxvt - lightweight multi-tabbed terminal emulator
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f403ad5a908fcd38a55ed0a7e1b85584cb77be8781199653a39b8af1a9ad10d7
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/materm/files/mrxvt%20source/0.5.4/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		terminal/mrxvt
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS +=	--enable-everything
CONFIGURE_OPTIONS +=	--disable-debug

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
