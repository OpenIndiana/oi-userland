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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libsodium
COMPONENT_VERSION= 1.0.12
COMPONENT_SUMMARY= Sodium crypto library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b8648f1bb3a54b0251cf4ffa4f0d76ded13977d4fa7517d988f4c902dd8e2f95
COMPONENT_ARCHIVE_URL= \
  https://github.com/jedisct1/libsodium/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://download.libsodium.org/doc/
COMPONENT_FMRI= library/security/libsodium
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE = ISC
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

