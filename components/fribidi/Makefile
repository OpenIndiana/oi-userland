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

COMPONENT_NAME= fribidi

COMPONENT_VERSION= 0.19.6
COMPONENT_SUMMARY= Free Implementation of the Unicode Bidirectional Algorithm
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:cba8b7423c817e5adf50d28ec9079d14eafcec9127b9e8c8f1960c5ad585e17d
COMPONENT_ARCHIVE_URL= \
  http://fribidi.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://fribidi.org/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
