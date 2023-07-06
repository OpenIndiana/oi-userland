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
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		uchardet
COMPONENT_VERSION=	0.0.8
COMPONENT_SUMMARY=	uchardet is an encoding detector library
COMPONENT_DESCRIPTION=	uchardet is an encoding detector library, which takes a sequence of bytes in an unknown character encoding \
						without any additional information, and attempts to determine the encoding of the text. \
						Returned encoding names are iconv-compatible.
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/uchardet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://www.freedesktop.org/software/uchardet/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:e97a60cfc00a1c147a674b097bb1422abd9fa78a2d9ce3f3fdcc2e78a34ac5f0
COMPONENT_FMRI=		library/uchardet
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MPLv1.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_TEST_TRANSFORMS += \
	' -e "s/ [0-9]*\.[0-9]* sec//" ' \
	' -e "/Total Test time/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
