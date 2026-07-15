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
# Copyright 2026 Benjamin S. Osenbach
#

BUILD_BITS=64 # for binaries or 32_and_64 for libraries
BUILD_STYLE=cargo
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=zoxide
COMPONENT_VERSION=0.10.0
COMPONENT_SUMMARY= A smarter cd command. Supports all major shells
COMPONENT_PROJECT_URL=https://github.com/ajeetdsouza/zoxide
COMPONENT_FMRI=application/zoxide
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://github.com/ajeetdsouza/zoxide/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=sha256:4fcd4272b013a10b637dbcc299c58a9924b94470a9042677ca1a204cc2e9150e
COMPONENT_LICENSE=MIT
COMPONENT_LICENSE_FILE=LICENSE
TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

# Build dependencies
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
