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

COMPONENT_NAME=pipes.sh
COMPONENT_VERSION=1.3.0
COMPONENT_SUMMARY= Animated pipes terminal screensaver
COMPONENT_PROJECT_URL=https://github.com/pipeseroni/pipes.sh
COMPONENT_FMRI=application/pipes.sh
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://github.com/pipeseroni/pipes.sh/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=sha256:532976dd8dc2d98330c45a8bcb6d7dc19e0b0e30bba8872dcce352361655a426 
COMPONENT_LICENSE=MIT
COMPONENT_LICENSE_FILE=pipes.sh.license
TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES+=shell/bash
# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
