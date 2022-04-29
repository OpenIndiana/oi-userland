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

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libdvdread
COMPONENT_VERSION=      6.0.1
COMPONENT_FMRI=         library/video/libdvdread
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SUMMARY=      Library for reading DVD video disks
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:28ce4f0063883ca4d37dfd40a2f6685503d679bca7d88d58e04ee8112382d5bd
COMPONENT_ARCHIVE_URL=  \
	http://download.videolan.org/pub/videolan/libdvdread/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://dvdnav.mplayerhq.hu
COMPONENT_LICENSE=      GPLv2.0
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D); autoreconf -f -i )

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
