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
COMPONENT_VERSION=      3.2.16
COMPONENT_SUMMARY=      Implementation of the olm and megolm cryptographic ratchets
COMPONENT_PROJECT_URL=  https://gitlab.matrix.org/matrix-org/olm
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:327cfcb81ef0c42f4b1d5c24b25d56932b57d64ccd9f00ed919a893a43333411
COMPONENT_ARCHIVE_URL=	https://gitlab.matrix.org/matrix-org/$(COMPONENT_NAME)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/olm
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_LICENSE=      Apache License 2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DOLM_TESTS=NO

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
