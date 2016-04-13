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

COMPONENT_NAME= libdvdread
COMPONENT_VERSION= 5.0.3
COMPONENT_FMRI = library/video/libdvdread
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= Library for reading DVD video disks
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:321cdf2dbdc83c96572bc583cd27d8c660ddb540ff16672ecb28607d018ed82b
COMPONENT_ARCHIVE_URL= \
  http://download.videolan.org/pub/videolan/libdvdread/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://dvdnav.mplayerhq.hu
COMPONENT_LICENSE = GPLv2.0
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH = /usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/etc

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
