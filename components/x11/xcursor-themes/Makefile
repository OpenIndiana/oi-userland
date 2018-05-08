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

COMPONENT_NAME=           xcursor-themes
COMPONENT_VERSION=        1.0.5
COMPONENT_SUMMARY=        Cursor themes from X.Org
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_FMRI=           x11/data/xcursor-themes
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:ae8381d39096598f7fe93fbd3ab079d93347a989f29e017f399ffcd20c8e1272
COMPONENT_ARCHIVE_URL=    $(XORG_DATA_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=        MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += x11/library/libxcursor

# Auto-generated dependencies
REQUIRED_PACKAGES += image/xcursorgen
