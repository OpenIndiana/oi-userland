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
# Copyright 2022-2023 Niklas Poslovski
#

BUILD_STYLE=cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         msgpack
COMPONENT_VERSION=      6.0.0
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://msgpack.org
COMPONENT_SUMMARY=      An efficient object serialization library
COMPONENT_FMRI=         library/msgpack
COMPONENT_SRC=          $(COMPONENT_NAME)-c-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:3654f5e2c652dc52e0a993e270bb57d5702b262703f03771c152bba51602aeba
COMPONENT_ARCHIVE_URL=	https://github.com/msgpack/msgpack-c/releases/download/c-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_LICENSE=      Boost
COMPONENT_LICENSE_FILE= LICENSE_1_0.txt

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DMSGPACK_BUILD_TESTS=Off
CMAKE_OPTIONS += -DMSGPACK_ENABLE_STATIC=Off

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
