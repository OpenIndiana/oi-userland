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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gphoto2
COMPONENT_VERSION= 2.5.32
COMPONENT_SUMMARY= Digital camera utility
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL = https://github.com/gphoto/
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4b87dc03a0eb0677ac9158f2d38c6857da65f14514820743e8eef40350d5a3f6
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gphoto/files/gphoto/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
$(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION = Applications/Graphics and Imaging
COMPONENT_FMRI = desktop/gphoto2
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += -std=c99 $(XPG6MODE)

# test021 fails because it tries to access files only accessible by root

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += library/aalib
REQUIRED_PACKAGES += library/libgphoto2-2
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += system/library
