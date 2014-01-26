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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= idzebra

COMPONENT_VERSION= 2.0.56
COMPONENT_SUMMARY= idzebra - text indexing and retrieval engine
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:12d293e84dfe55b2e5089fbf55169a8f9d396d9e3bf0211ff0eeafd4a047ee73
COMPONENT_ARCHIVE_URL= \
  http://ftp.indexdata.dk/pub/zebra/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.indexdata.dk/zebra

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
