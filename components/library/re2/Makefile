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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         re2
COMPONENT_VERSION=      2025.7.22
HUMAN_VERSION=          2025-07-22
COMPONENT_SUMMARY=      Fast, safe, thread-friendly regular expression engine
COMPONENT_PROJECT_URL=  https://github.com/google/re2
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f54c29f1c3e13e12693e3d6d1230554df3ab3a1066b2e1f28c5330bfbf6db1e3
COMPONENT_ARCHIVE_URL=	https://github.com/google/$(COMPONENT_NAME)/releases/download/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/re2
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

COMPONENT_TEST_CMD= ./runtests

# Manually added build dependencies
TEST_REQUIRED_PACKAGES += developer/googletest

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/abseil-cpp
REQUIRED_PACKAGES += library/c++/abseil-cpp-2501
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
