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

COMPONENT_NAME= libdvdnav
COMPONENT_VERSION= 5.0.3
COMPONENT_FMRI = library/video/libdvdnav
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= DVD navigation library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:5097023e3d2b36944c763f1df707ee06b19dc639b2b68fb30113a5f2cbf60b6d
COMPONENT_ARCHIVE_URL= \
  http://download.videolan.org/pub/videolan/libdvdnav/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://dvdnav.mplayerhq.hu
COMPONENT_LICENSE = GPLv2.0
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/video/libdvdread
REQUIRED_PACKAGES += system/library
