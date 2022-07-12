#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 erwinlem
#

BUILD_STYLE=cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cereal
COMPONENT_VERSION=	1.3.2
COMPONENT_SUMMARY=	A C++11 library for serialization
COMPONENT_PROJECT_URL=	https://uscilab.github.io/cereal/
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/C++
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/USCiLab/cereal/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:16a7ad9b31ba5880dac55d62b5d6f243c3ebc8d46a3514149e56b5e7ea81f85f
COMPONENT_LICENSE=	BSD3CLAUSE
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS+= -DBUILD_TESTS=OFF

# Auto-generated dependencies
