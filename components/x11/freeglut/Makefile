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
# Copyright 2015-2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           freeglut
COMPONENT_VERSION=        3.0.0
COMPONENT_REVISION=       1
COMPONENT_FMRI=           x11/library/freeglut
COMPONENT_SUMMARY= \
  freeglut - open-source alternative to the OpenGL Utility Toolkit (GLUT) library
COMPONENT_PROJECT_URL = http://freeglut.sourceforge.net/
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:2a43be8515b01ea82bcfa17d29ae0d40bd128342f0930cd1f375f1ff999f76a2
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/project/freeglut/freeglut/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DFREEGLUT_BUILD_DEMOS=OFF
CMAKE_OPTIONS+= -DFREEGLUT_BUILD_STATIC_LIBS=OFF

CPPFLAGS += -D__posix__ -D__unix__

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxxf86vm
