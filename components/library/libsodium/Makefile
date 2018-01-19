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
COMPONENT_VERSION= 1.0.13
COMPONENT_SUMMARY= Sodium crypto library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:9c13accb1a9e59ab3affde0e60ef9a2149ed4d6e8f99c93c7a5b97499ee323fd
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

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
