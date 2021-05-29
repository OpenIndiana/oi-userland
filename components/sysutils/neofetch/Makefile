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
# Copyright 2021 Benjamin S. Osenbach
#

BUILD_BITS=64 # for binaries or 32_and_64 for libraries
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=neofetch
COMPONENT_VERSION=7.1.0
COMPONENT_SUMMARY= A command-line system information tool written in bash 3.2+
COMPONENT_PROJECT_URL=https://github.com/dylanaraps/neofetch
COMPONENT_FMRI=application/neofetch
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://github.com/dylanaraps/neofetch/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=sha256:58a95e6b714e41efc804eca389a223309169b2def35e57fa934482a6b47c27e7
COMPONENT_LICENSE=MIT
COMPONENT_LICENSE_FILE=neofetch.license
TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES+=shell/bash
# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
