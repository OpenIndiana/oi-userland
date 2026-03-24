#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Rouven Weiler
# Copyright 2024 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wavpack
COMPONENT_VERSION=	5.9.0
COMPONENT_SUMMARY=	wavpack - Hybrid Lossless Audio Compression
COMPONENT_PROJECT_URL=	https://www.wavpack.com/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:b0038f515d322042aaa6bd352d437729c6f5f904363cc85bbc9b0d8bd4a81927
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			audio/wavpack
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=		BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/common.mk

# gcc 14 complains about incompatible pointer types
CFLAGS += -Wno-error=incompatible-pointer-types

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-legacy

COMPONENT_TEST_TRANSFORMS= \
	' -n ' \
	' -e "s/([^)]*)//" ' \
	' -e "/PASS/p" ' \
	' -e "/pass/p" ' \
	' -e "/\*\*\*/p" ' \
	' -e "/===/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
