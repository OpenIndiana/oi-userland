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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libsodium
COMPONENT_VERSION= 1.0.20
COMPONENT_SUMMARY= Sodium is an easy-to-use software library for encryption, decryption, signatures, password hashing, and more
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ebb65ef6ca439333c2bb41a0c1990587288da07f6c7fd07cb3a18cc18d30ce19
COMPONENT_ARCHIVE_URL=	https://download.libsodium.org/$(COMPONENT_NAME)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://download.libsodium.org/doc/
COMPONENT_FMRI= library/security/libsodium
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE= ISC
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
