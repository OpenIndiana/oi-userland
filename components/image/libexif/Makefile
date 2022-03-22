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
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libexif
COMPONENT_RELEASE= 0.6
COMPONENT_VERSION= $(COMPONENT_RELEASE).24
COMPONENT_SUMMARY= EXIF tag parsing library for digital cameras
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e5f15eeab693028cfdc4c0d78f024e1ca78baa0e1f636dc443395e9fbb0a2b7a
COMPONENT_ARCHIVE_URL= https://github.com/libexif/libexif/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL= https://libexif.github.io/
COMPONENT_FMRI= image/library/libexif
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_CLASSIFICATION= System/Multimedia Libraries

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-docs

unexport SHELLOPTS
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/XPASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/XFAIL:/p" ' \
	'-e "/ERROR:/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
