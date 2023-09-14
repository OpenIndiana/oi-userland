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
# Copyright 2023 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libpsl
COMPONENT_VERSION= 0.21.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Public Suffix List Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e35991b6e17001afa2c0ca3b10c357650602b92596209b7492802f3768a6285f
COMPONENT_ARCHIVE_URL= https://github.com/rockdaboot/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://github.com/rockdaboot/$(COMPONENT_NAME)
COMPONENT_FMRI= library/libpsl
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH=i $(PATH.gnu)
CONFIGURE_OPTIONS += --enable-static=no

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += system/library
