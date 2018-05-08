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
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xwd
COMPONENT_VERSION=        1.0.7
COMPONENT_SUMMARY=        xwd - utility for dumping an image of an X window
COMPONENT_PROJECT_URL =   $(XORG_PROJECT_URL)
COMPONENT_FMRI=           x11/xwd
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:cd6815b8b9e0b98e284d3d732fb12162159cb9dcee4f45a7d4c0bd8b308a6794
COMPONENT_ARCHIVE_URL=    $(XORG_APP_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=        MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += x11/header/xproto
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxkbfile
