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
# Copyright (c) 2023 Niklas Poslovski
#
BUILD_STYLE=cmake
USE_DEFAULT_TEST_TRANSFORMS=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         hiredis
COMPONENT_VERSION=      1.2.0
COMPONENT_PROJECT_URL=  https://github.com/redis/hiredis
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:82ad632d31ee05da13b537c124f819eb88e18851d9cb0c30ae0552084811588c
COMPONENT_ARCHIVE_URL=  https://github.com/redis/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_SUMMARY=      Minimalistic C client for Redis >= 1.2
COMPONENT_FMRI=         database/hiredis
COMPONENT_CLASSIFICATION=System/Databases
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_CMD = $(BUILD_DIR)/$(MACH64)/hiredis-test
COMPONENT_TEST_TRANSFORMS += '-e "s/: [0-9].[0-9][0-9][0-9]s//" '
COMPONENT_TEST_TRANSFORMS += '-e "s/: [0-9][0-9].[0-9][0-9][0-9]s//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
