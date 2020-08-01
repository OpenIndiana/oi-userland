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
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libmypaint
COMPONENT_VERSION= 1.6.1
COMPONENT_SUMMARY= MyPaint Brush Library
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:741754f293f6b7668f941506da07cd7725629a793108bb31633fb6c3eae5315f
COMPONENT_ARCHIVE_URL= \
  https://github.com/mypaint/libmypaint/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://github.com/mypaint/libmypaint
COMPONENT_LICENSE= ISC
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI= library/libmypaint

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/TOTAL|PASS|FAIL|XFAIL|SKIP|XPASS|ERROR/'"

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
