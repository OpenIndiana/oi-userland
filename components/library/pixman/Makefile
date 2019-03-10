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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pixman
COMPONENT_VERSION=	0.38.0
COMPONENT_PROJECT_URL=	http://www.pixman.org/
COMPONENT_SUMMARY=	Pixman: The pixel-manipulation library for X and Cairo
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:a7592bef0156d7c27545487a52245669b00cf7e70054505381cff2136d890ca8
COMPONENT_ARCHIVE_URL=	http://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI=		library/graphics/pixman
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --disable-gtk

# The test suite needs this
unexport SHELLOPTS

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
