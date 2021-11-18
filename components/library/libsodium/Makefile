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
BUILD_BITS=64_and_32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libsodium
COMPONENT_VERSION= 1.0.18
COMPONENT_SUMMARY= Sodium crypto library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:6f504490b342a4f8a4c4a02fc9b866cbef8622d5df4e5452b46be121e46636c1
COMPONENT_ARCHIVE_URL= \
  https://download.libsodium.org/$(COMPONENT_NAME)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://download.libsodium.org/doc/
COMPONENT_FMRI= library/security/libsodium
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE = ISC
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_MAKE_RULES)/common.mk

# pynacl tests dump core with -O3
gcc_OPT = -O2

# For tests to pass
unexport SHELLOPTS

CONFIGURE_OPTIONS += --disable-static

COMPONENT_TEST_TRANSFORMS += \
	'-e "/\/usr\/gnu\/bin\/make/d"' \
	'-e "/CC/d"' \
	'-e "/Making/d"' \
	'-e "/make/d"' \
	'-e "/Nothing to be done/d"' \
	'-e "/Leaving directory/d"' \
	'-e "/Entering directory/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
