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
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libdvbpsi
COMPONENT_VERSION= 1.3.3
COMPONENT_FMRI = library/video/libdvbpsi
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= A simple library designed for decoding and generation of MPEG TS and DVB PSI tables
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:02b5998bcf289cdfbd8757bedd5987e681309b0a25b3ffe6cebae599f7a00112
COMPONENT_ARCHIVE_URL=	https://download.videolan.org/pub/libdvbpsi/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.videolan.org/developers/libdvbpsi.html
COMPONENT_LICENSE = LGPLv2.1

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket -lnsl

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
