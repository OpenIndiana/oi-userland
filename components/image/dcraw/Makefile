#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2015 Alexander Pyhalov
#

BUILD_BITS=				64
BUILD_STYLE=			justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			dcraw
COMPONENT_VERSION=		9.28.0
COMPONENT_PROJECT_URL=	https://www.dechifro.org/dcraw/
COMPONENT_SUMMARY=		dcraw - Decoding RAW digital photos
COMPONENT_SRC=			$(COMPONENT_NAME)
COMPONENT_ARCHIVE=		$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:2890c3da2642cd44c5f3bfed2c9b2c1db83da5cec09cc17e0fa72e17541fb4b9
COMPONENT_ARCHIVE_URL=	https://www.dechifro.org/dcraw/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		GPLv2
COMPONENT_FMRI=			image/dcraw
COMPONENT_CLASSIFICATION=	System/Media

TEST_TARGET=			$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION=( cd $(@D) && rm -f install )

# build with the distribution preferred libjpeg implementation
CFLAGS               += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS             += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS              += $(JPEG_LDFLAGS)

COMPONENT_BUILD_ARGS += CC=$(CC)
COMPONENT_BUILD_ARGS += CXX=$(CXX)
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"

# Manually changed dependency:
REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)

# Auto-generated dependencies
REQUIRED_PACKAGES += codec/jasper
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
