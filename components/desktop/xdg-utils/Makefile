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

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdg-utils
COMPONENT_VERSION=	1.2.1
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/xdg-utils/
COMPONENT_SUMMARY=	The Portland Project's desktop integration tools
COMPONENT_FMRI=		desktop/xdg/xdg-utils
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:3288aad73c764569e1d06d8368af28688bbba0549cf727e2278886fe66605c81
COMPONENT_ARCHIVE_URL=	https://gitlab.freedesktop.org/xdg/xdg-utils/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	MIT

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_NAME)-v$(COMPONENT_VERSION)-356c380ad6fecc9ce6bea1f6a77986ba67402c80 $(COMPONENT_SRC) )
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
