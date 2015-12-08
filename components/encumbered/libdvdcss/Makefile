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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libdvdcss
COMPONENT_VERSION= 1.3.0
COMPONENT_FMRI = library/video/libdvdcss
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= A simple library designed for accessing DVDs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
 sha256:7c414acd520c4e4dd7267952f72d738ff50321a7869af4d75c65aefad44f1395
COMPONENT_ARCHIVE_URL= \
  http://download.videolan.org/pub/videolan/libdvdcss/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.videolan.org/developers/libdvdcss.html
COMPONENT_LICENSE = GPLv2.0
COMPONENT_LICENSE_FILE = $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
