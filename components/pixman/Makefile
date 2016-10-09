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

COMPONENT_NAME=		pixman
COMPONENT_VERSION=	0.34.0
COMPONENT_PROJECT_URL=	http://www.pixman.org/
COMPONENT_SUMMARY=	Pixman: The pixel-manipulation library for X and Cairo
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:21b6b249b51c6800dc9553b65106e1e37d0e25df942c90531d4c3997aa20a88e
COMPONENT_ARCHIVE_URL=	http://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI=		library/graphics/pixman
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	MIT

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --disable-gtk

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
