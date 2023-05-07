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

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         olm
COMPONENT_VERSION=      3.2.15
COMPONENT_SUMMARY=      Implementation of the olm and megolm cryptographic ratchets
COMPONENT_PROJECT_URL=  https://gitlab.matrix.org/matrix-org/olm
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:543f14f58a5ff7187f62f28afedfeba246fd0f28fccdad259dee82215b91298d
COMPONENT_ARCHIVE_URL=	https://gitlab.matrix.org/matrix-org/$(COMPONENT_NAME)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/olm
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_LICENSE=      Apache License 2.0
COMPONENT_LICENSE_FILE=	LICENSE

CMAKE_OPTIONS += -DOLM_TESTS=NO

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
