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
# Copyright (c) 2019 Michal Nowak
# Copyright (c) 2021, 2024 Andreas Wacknitz
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pixman
COMPONENT_VERSION=	0.44.2
COMPONENT_SUMMARY=	Pixman: The pixel-manipulation library for X and Cairo
COMPONENT_PROJECT_URL=	https://www.pixman.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:6349061ce1a338ab6952b92194d1b0377472244208d47ff25bef86fc71973466
COMPONENT_ARCHIVE_URL=	https://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/graphics/pixman
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)

PATH= $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
