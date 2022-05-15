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
# Copyright 2017 Alexander Pyhalov
# Copyright 2022 Andreas Wacknitz
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gphoto2
COMPONENT_VERSION= 2.5.28
COMPONENT_SUMMARY= Digital camera utility
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL = https://github.com/gphoto/
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:54097ee429f57a9f076a814590f777cebbc837879fe7b16e41b2615e347f6ae0
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gphoto/files/gphoto/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
$(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION = Applications/Graphics and Imaging
COMPONENT_FMRI = desktop/gphoto2
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS+= -std=c99 $(CPP_XPG6MODE)

# build with the distribution preferred libjpeg implementation
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

unexport SHELLOPTS

# test031 fails

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += library/aalib
REQUIRED_PACKAGES += library/libgphoto2-2
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
