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
# Copyright 2023 Niklas Poslovski
#

BUILD_BITS = 64_and_32
BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           freeglut
COMPONENT_VERSION=        3.4.0
COMPONENT_FMRI=           x11/library/freeglut
COMPONENT_SUMMARY= \
  freeglut - open-source alternative to the OpenGL Utility Toolkit (GLUT) library
COMPONENT_PROJECT_URL = https://freeglut.sourceforge.net/
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:3c0bcb915d9b180a97edaebd011b7a1de54583a838644dcd42bb0ea0c6f3eaec
COMPONENT_ARCHIVE_URL= \
  https://downloads.sourceforge.net/project/freeglut/freeglut/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT License

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DFREEGLUT_BUILD_DEMOS=OFF
CMAKE_OPTIONS+= -DFREEGLUT_BUILD_STATIC_LIBS=OFF

CPPFLAGS += -D__posix__ -D__unix__

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxxf86vm
