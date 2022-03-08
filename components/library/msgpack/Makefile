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
# Copyright 2022 Niklas Poslovski
#

BUILD_BITS=64
BUILD_STYLE=cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         msgpack
COMPONENT_VERSION=      4.0.0
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://msgpack.org
COMPONENT_SUMMARY=      An efficient object serialization library
COMPONENT_FMRI=         library/msgpack
COMPONENT_SRC=          $(COMPONENT_NAME)-c-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:420fe35e7572f2a168d17e660ef981a589c9cbe77faa25eb34a520e1fcc032c8
COMPONENT_ARCHIVE_URL=	https://github.com/msgpack/msgpack-c/releases/download/c-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_LICENSE=      Boost
COMPONENT_LICENSE_FILE= msgpack.license

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
