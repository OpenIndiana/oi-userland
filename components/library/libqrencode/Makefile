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
# Copyright (c) 2021 Andreas Wacknitz
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				libqrencode
COMPONENT_VERSION=			4.1.1
COMPONENT_PROJECT_URL=		https://github.com/fukuchi/libqrencode
COMPONENT_SUMMARY=			A fast and compact QR Code encoding library
COMPONENT_SRC=				$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=			$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:5385bc1b8c2f20f3b91d258bf8ccc8cf62023935df2d2676b5b67049f31a049c
COMPONENT_ARCHIVE_URL=		https://github.com/fukuchi/libqrencode/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_FMRI=         	library/libqrencode
COMPONENT_LICENSE=      	LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DWITH_TESTS=ON

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9. ]*sec//g"' \
	'-e "s/Total Test time (real) =//g"'

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += system/library
