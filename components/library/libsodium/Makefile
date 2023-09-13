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
# Copyright 2018 Alexander Pyhalov
# Copyright (c) 2021 Tim Mooney.  All rights reserved
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libsodium
COMPONENT_VERSION= 1.0.19
COMPONENT_SUMMARY= Sodium crypto library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:018d79fe0a045cca07331d37bd0cb57b2e838c51bc48fd837a1472e50068bbea
COMPONENT_ARCHIVE_URL=	https://download.libsodium.org/$(COMPONENT_NAME)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://download.libsodium.org/doc/
COMPONENT_FMRI= library/security/libsodium
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE= ISC
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION = ( $(MV) $(COMPONENT_NAME)-stable $(COMPONENT_SRC) )

# pynacl tests dump core with -O3
#gcc_OPT = -O2

CONFIGURE_OPTIONS += --disable-static

# For tests to pass
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
