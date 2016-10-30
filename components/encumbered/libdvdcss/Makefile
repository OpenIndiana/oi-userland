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
COMPONENT_VERSION= 1.4.0
COMPONENT_FMRI = library/video/libdvdcss
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= A simple library designed for accessing DVDs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2089375984800df29a4817b37f3123c1706723342d6dab4d0a8b75c25c2c845a
COMPONENT_ARCHIVE_URL= \
  http://download.videolan.org/pub/videolan/libdvdcss/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.videolan.org/developers/libdvdcss.html
COMPONENT_LICENSE = GPLv2.0
COMPONENT_LICENSE_FILE = $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CFLAGS+= $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += system/library
