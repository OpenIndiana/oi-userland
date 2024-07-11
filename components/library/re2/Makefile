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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         re2
COMPONENT_VERSION=      2024.7.2
HUMAN_VERSION=          2024-07-02
COMPONENT_SUMMARY=      Fast, safe, thread-friendly regular expression engine
COMPONENT_PROJECT_URL=  https://github.com/google/re2
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:eb2df807c781601c14a260a507a5bb4509be1ee626024cb45acbd57cb9d4032b
COMPONENT_ARCHIVE_URL=	https://github.com/google/$(COMPONENT_NAME)/releases/download/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/re2
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= LICENSE

# Tests require Googletest which we don't have yet.
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/abseil-cpp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
