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
# Copyright (c) 2021, 2023 Andreas Wacknitz
#

BUILD_STYLE= meson
BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pixman
COMPONENT_VERSION=	0.43.2
COMPONENT_SUMMARY=	Pixman: The pixel-manipulation library for X and Cairo
COMPONENT_PROJECT_URL=	https://www.pixman.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ea79297e5418fb528d0466e8b5b91d1be88857fa3706f49777b2925a72ae9924
COMPONENT_ARCHIVE_URL=	https://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/graphics/pixman
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# The test suite needs this
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
