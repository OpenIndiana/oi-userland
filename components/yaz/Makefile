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

COMPONENT_NAME= yaz

COMPONENT_VERSION= 5.0.12
COMPONENT_SUMMARY= toolkit supporting the development of Z39.50/SRW/SRU clients and servers
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4501bbeee665e34ad480508e83fbe8b65d2b5fd0a8194077f1b4235b616a846e
COMPONENT_ARCHIVE_URL= \
  http://ftp.indexdata.dk/pub/yaz/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.indexdata.dk/yaz

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk


CONFIGURE_OPTIONS += --without-icu

# Without this tests fail
ENV=/usr/bin/env -i

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
