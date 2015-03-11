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
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gmtp
COMPONENT_VERSION=	1.3.9
COMPONENT_PROJECT_URL=	http://gmtp.sourceforge.net/
COMPONENT_SUMMARY=	A simple MP3 and Media player client for UNIX and UNIX like systems
COMPONENT_FMRI=		system/media/gmtp
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5bff5385db66f5c3e82d89edb7ca4a8ccb8c8954faf7341438080f2741dcbd2d
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/gmtp/files/gMTP-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
