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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved
# Copyright (c) 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		desktop-file-utils
COMPONENT_VERSION=	0.24
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/desktop-file-utils/
COMPONENT_SUMMARY=	A few command line utilities for working with desktop entries
COMPONENT_FMRI=		library/desktop/desktop-file-utils
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Scripts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:a1de5da60cbdbe91e5c9c10ac9afee6c3deb019e0cee5fdb9a99dddc245f83d9
COMPONENT_ARCHIVE_URL=	http://www.freedesktop.org/software/desktop-file-utils/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
