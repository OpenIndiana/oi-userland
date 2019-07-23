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

COMPONENT_NAME= x264
COMPONENT_LIB_VERSION= 157
COMPONENT_SNAPSHOT_DATE= 20190721
COMPONENT_VERSION= snapshot-$(COMPONENT_SNAPSHOT_DATE)-2245-stable
IPS_COMPONENT_VERSION= 0.$(COMPONENT_LIB_VERSION).0.$(COMPONENT_SNAPSHOT_DATE)
COMPONENT_FMRI = library/video/x264
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= H.264 encoder library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:1da29c2d745fce49c6c4822ae191a32ae761e6c163046090cdb744ceb6b45024
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.videolan.org/pub/videolan/x264/snapshots/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.videolan.org/developers/x264.html
COMPONENT_LICENSE = GPLv2.0
COMPONENT_LICENSE_FILE = COPYING

PKG_MACROS += COMPONENT_LIB_VERSION=$(COMPONENT_LIB_VERSION)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

CFLAGS.32 = -D_FILE_OFFSET_BITS=64
CFLAGS += $(CFLAGS.$(BITS))

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-pic
CONFIGURE_OPTIONS += --extra-cflags="$(CFLAGS)"
CONFIGURE_OPTIONS += --extra-ldflags="$(LDFLAGS)"
CONFIGURE_OPTIONS += --disable-cli
CONFIGURE_OPTIONS += --enable-shared

CONFIGURE_ENV.64 = host="amd64-pc-solaris2.11"
CONFIGURE_ENV += $(CONFIGURE_ENV.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
