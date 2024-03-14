#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Aurelien Larcher
#
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     xcb-util-errors
COMPONENT_VERSION=  1.0.1
COMPONENT_SUMMARY=  The X protocol C-language Binding (XCB): utility library giving human readble names to error codes and event codes
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:5628c87b984259ad927bacd8a42958319c36bdf4b065887803c9d820fb80f357
COMPONENT_PROJECT_URL=	https://xcb.freedesktop.org/
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/dist/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         x11/library/xcb-util-errors
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=      MIT License

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
