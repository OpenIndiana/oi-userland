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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xcb-util-errors
COMPONENT_VERSION=        1.0
COMPONENT_FMRI=           x11/library/xcb-util-errors
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  The X protocol C-language Binding (XCB): utility library giving human readble names to error codes and event codes
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:682681769e818ba085870d1ccd65f1f282ca16ca7d6f0f73ee70bc3642aa1995
COMPONENT_ARCHIVE_URL= \
  http://xcb.freedesktop.org/dist/xcb-util-errors-1.0.tar.bz2
COMPONENT_PROJECT_URL = http://xcb.freedesktop.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xcb-util-errors.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
