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
# Copyright 2016 Alexander Pyhalov
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libdiscid
COMPONENT_VERSION= 0.6.4
COMPONENT_SUMMARY= Library for creating MusicBrainz DiscIDs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:dd5e8f1c9aead442e23b749a9cc9336372e62e88ad7079a2b62895b0390cb282
COMPONENT_ARCHIVE_URL= http://ftp.musicbrainz.org/pub/musicbrainz/libdiscid/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://musicbrainz.org/doc/libdiscid
COMPONENT_FMRI= library/musicbrainz/libdiscid
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
