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
COMPONENT_VERSION= 1.0.8
COMPONENT_SUMMARY= Sodium crypto library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:c0f191d2527852641e0a996b7b106d2e04cbc76ea50731b2d0babd3409301926
COMPONENT_ARCHIVE_URL= \
  https://github.com/jedisct1/libsodium/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://download.libsodium.org/doc/
COMPONENT_FMRI= library/security/libsodium
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE = ISC
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# For tests to pass
ENV=/usr/bin/env -i

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
