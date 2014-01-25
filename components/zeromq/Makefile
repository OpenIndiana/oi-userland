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

COMPONENT_NAME= zeromq

COMPONENT_VERSION= 3.2.4
COMPONENT_SUMMARY= Open source message queue optimised for performance
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:df96a141c85b65c2cb6c0db22223126623a09eecbfccb7f74400f3f938742f59
COMPONENT_ARCHIVE_URL= \
  http://download.zeromq.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://zeromq.org/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX= /usr/g++

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# test_shutdown_stress fails 
test: $(TEST_32_and_64)
