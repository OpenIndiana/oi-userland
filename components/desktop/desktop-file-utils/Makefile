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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		desktop-file-utils
COMPONENT_VERSION=	0.23
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/desktop-file-utils/
COMPONENT_SUMMARY=	A few command line utilities for working with desktop entries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:6c094031bdec46c9f621708f919084e1cb5294e2c5b1e4c883b3e70cb8903385
COMPONENT_ARCHIVE_URL=	http://www.freedesktop.org/software/desktop-file-utils/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
