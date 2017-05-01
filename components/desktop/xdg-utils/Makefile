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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdg-utils
COMPONENT_VERSION=	1.0.2
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/xdg-utils/
COMPONENT_SUMMARY=	The Portland Project's desktop integration tools
COMPONENT_FMRI=		desktop/xdg/xdg-utils
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:21aeb7d16b2529b8d3975118f59eec09953e09f9a68d718159e98c90474b01ac
COMPONENT_ARCHIVE_URL=	http://portland.freedesktop.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PRE_CONFIGURE_ACTION = (cp -rp $(SOURCE_DIR)/* $(@D))

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
