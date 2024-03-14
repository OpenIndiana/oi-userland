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

BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         nlohmann-json
COMPONENT_VERSION=      3.11.2
COMPONENT_PROJECT_URL=  https://github.com/nlohmann/json
COMPONENT_SUMMARY=      JSON for Modern C++
COMPONENT_FMRI=         library/c++/nlohmann-json
COMPONENT_SRC=          json
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:8c4b26bf4b422252e13f332bc5e388ec0ab5c3443d24399acb675e68278d341f
COMPONENT_ARCHIVE_URL=	https://github.com/nlohmann/json/releases/download/v$(COMPONENT_VERSION)/json.tar.xz
COMPONENT_CLASSIFICATION=       Development/C++
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE.MIT

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DJSON_BuildTests=OFF

# Auto-generated dependencies
