#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Carter Li
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           fastfetch
COMPONENT_VERSION=        2.21.0
COMPONENT_SUMMARY=        An actively maintained, feature-rich and performance oriented, neofetch like system information tool
COMPONENT_PROJECT_URL=    https://github.com/fastfetch-cli/fastfetch
COMPONENT_FMRI=           application/fastfetch
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    https://github.com/fastfetch-cli/fastfetch/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:21d085a612b6bd9ab0f4e7bffe2632e313e6f67d432251cfd5a7f877b7194733
COMPONENT_LICENSE=        MIT
COMPONENT_LICENSE_FILE=   LICENSE

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DSET_TWEAK=Off
CMAKE_OPTIONS += -DENABLE_LTO=Off

COMPONENT_TEST_CMD = ./fastfetch --list-features && ./fastfetch

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
