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
# Copyright 2021 Jean-Pierre André. All rights reserved.
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= exfat
IPS_COMPONENT_VERSION= 1.3.0
COMPONENT_VERSION= $(IPS_COMPONENT_VERSION)
COMPONENT_SUMMARY= exfat - Utilities that provide access to exFAT
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:689bcb4a639acd2d45e6fa0ff455f7f18edb2421d4f4f42909943775adc0e375
COMPONENT_ARCHIVE_URL= https://github.com/relan/exfat/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://github.com/relan/exfat
COMPONENT_FMRI= system/file-system/exfat
COMPONENT_CLASSIFICATION= System/Administration and Configuration
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= exfat.license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS += --exec-prefix=/usr

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += system/library
