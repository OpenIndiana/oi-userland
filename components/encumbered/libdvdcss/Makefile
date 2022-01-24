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

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libdvdcss
COMPONENT_VERSION=      1.4.3
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      A simple library designed for accessing DVDs
COMPONENT_PROJECT_URL=  https://www.videolan.org/developers/libdvdcss.html
COMPONENT_FMRI=         library/video/libdvdcss
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:233cc92f5dc01c5d3a96f5b3582be7d5cee5a35a52d3a08158745d3d86070079
COMPONENT_ARCHIVE_URL=  https://download.videolan.org/pub/videolan/libdvdcss/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2.0

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS+= $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
