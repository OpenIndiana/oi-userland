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
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libexif
COMPONENT_RELEASE= 0.6
COMPONENT_VERSION= $(COMPONENT_RELEASE).22
COMPONENT_SUMMARY= EXIF tag parsing library for digital cameras
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:5048f1c8fc509cc636c2f97f4b40c293338b6041a5652082d5ee2cf54b530c56
COMPONENT_ARCHIVE_URL= \
	https://github.com/libexif/libexif/releases/download/libexif-$(subst .,_,$(COMPONENT_VERSION))-release/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://sourceforge.net/projects/libexif
COMPONENT_FMRI= image/library/libexif
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_CLASSIFICATION= System/Multimedia Libraries

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-docs

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
