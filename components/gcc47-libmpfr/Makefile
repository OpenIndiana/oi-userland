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
# Copyright 2013 Andrzej Szeszo.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=mpfr
COMPONENT_VERSION=3.1.2
COMPONENT_SUMMARY="libmpfr - GCC 4.7 private copy"
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:79c73f60af010a30a5c27a955a1d2d01ba095b72537dab0ecaad57f5a7bb1b6b
COMPONENT_ARCHIVE_URL= \
  http://www.mpfr.org/mpfr-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX= /usr/gcc/4.7

CONFIGURE_OPTIONS+= --with-gmp=/usr/gcc/4.7

build:          $(BUILD_32)

install:        $(INSTALL_32)
