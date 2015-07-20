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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= opencore-amr
COMPONENT_VERSION= 0.1.3
COMPONENT_SUMMARY= OpenCORE AMR speech codec library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:106bf811c1f36444d7671d8fd2589f8b2e0cca58a2c764da62ffc4a070595385
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/opencore-amr/files/opencore-amr/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://opencore-amr.sourceforge.net/
COMPONENT_LICENSE = APLv2.0
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Media
COMPONENT_FMRI = codec/opencore-amr

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS += --disable-compile-c
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
