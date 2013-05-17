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

COMPONENT_NAME=gmp
COMPONENT_VERSION=5.0.5
COMPONENT_SUMMARY="libgmp - GCC 4.7 private copy"
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:1f588aaccc41bb9aed946f9fe38521c26d8b290d003c5df807f65690f2aadec9
COMPONENT_ARCHIVE_URL=  ftp://ftp.gmplib.org/pub/gmp/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX= /usr/gcc/4.7

CONFIGURE_OPTIONS+= --enable-cxx
CONFIGURE_OPTIONS+= CFLAGS="-fexceptions"

build:          $(BUILD_32)

install:        $(INSTALL_32)
