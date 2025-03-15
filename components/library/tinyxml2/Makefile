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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = cmake
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tinyxml2
COMPONENT_VERSION =		10.1.0
COMPONENT_SUMMARY =		Simple, small, efficient, C++ XML parser that can be easily integrated into other programs
COMPONENT_PROJECT_URL =		https://github.com/leethomason/tinyxml2
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL =		https://github.com/leethomason/tinyxml2/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	sha256:9da7e1aebbf180ef6f39044b9740a4e96fa69e54a01318488512ae92ca97a685
COMPONENT_FMRI =		library/tinyxml2
COMPONENT_CLASSIFICATION =	System/Libraries
COMPONENT_LICENSE =		Zlib
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Build shared library
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
