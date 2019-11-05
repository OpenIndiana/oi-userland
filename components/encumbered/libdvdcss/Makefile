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
COMPONENT_VERSION= 1.4.2
COMPONENT_SUMMARY= A simple library designed for accessing DVDs
COMPONENT_PROJECT_URL = http://www.videolan.org/developers/libdvdcss.html
COMPONENT_FMRI = library/video/libdvdcss
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:78c2ed77ec9c0d8fbed7bf7d3abc82068b8864be494cfad165821377ff3f2575
COMPONENT_ARCHIVE_URL= \
  http://download.videolan.org/pub/videolan/libdvdcss/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE = GPLv2.0

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CFLAGS+= $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
