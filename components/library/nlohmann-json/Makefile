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
COMPONENT_VERSION=      3.12.0
COMPONENT_SUMMARY=      JSON for Modern C++
COMPONENT_PROJECT_URL=  https://github.com/nlohmann/json
COMPONENT_SRC=          json
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:42f6e95cad6ec532fd372391373363b62a14af6d771056dbfc86160e6dfff7aa
COMPONENT_ARCHIVE_URL=	https://github.com/nlohmann/json/releases/download/v$(COMPONENT_VERSION)/json.tar.xz
COMPONENT_FMRI=         library/c++/nlohmann-json
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE.MIT

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DJSON_BuildTests=OFF

# Auto-generated dependencies
