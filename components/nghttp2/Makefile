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
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= nghttp2
COMPONENT_VERSION= 1.3.4
COMPONENT_SUMMARY= HTTP/2 C Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:63c1d70e50f0c8514e261be88b66720df095269791aa008d76c09e0c3a4c085f
COMPONENT_ARCHIVE_URL= \
  https://github.com/tatsuhiro-t/nghttp2/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://nghttp2.org/
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = MIT
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/nghttp2

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --disable-python-bindings
CONFIGURE_OPTIONS += --disable-app

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# test suite is empty
test: $(TEST_32_and_64)
