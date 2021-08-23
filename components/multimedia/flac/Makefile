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
# Copyright 2014 (c) Aurelien Larcher. All rights reserved.
#
BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		flac
COMPONENT_VERSION=	1.3.3
COMPONENT_FMRI=		codec/flac
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_PROJECT_URL=	https://flac.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:213e82bd716c9de6db2f98bcadbc4c24c7e2efe8c75939a1a84e28539c4e1748
COMPONENT_ARCHIVE_URL=\
	https://downloads.us.xiph.org/releases/flac/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_LICENSE=	Xiph.org BSD-style, binaries & media player plugins also use GPL v2, LGPL v2.1, documentation uses FDL v1.2
COMPONENT_SUMMARY=	An Open Source Lossless Audio Codec

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  += --enable-shared
CONFIGURE_OPTIONS  += --disable-xmms-plugin
ifeq   ($(MACH), i386)
CONFIGURE_OPTIONS  += --enable-sse
ifeq   ($(BITS), 32)
CONFIGURE_OPTIONS  += --enable-asm-optimizations
else
CONFIGURE_OPTIONS  += --disable-asm-optimizations
endif
else
CONFIGURE_OPTIONS  += --disable-sse
CONFIGURE_OPTIONS  += --disable-asm-optimizations
endif
CONFIGURE_OPTIONS  += --disable-altivec 

# One test is known to fail (failed also in the previous version 1.3.2)
# Testing the metadata-handling properties of flac-to-flac encoding...
# case00a...  ERROR: metadata does not match expected test/flac-to-flac-metadata-test-files/case00a-expect.meta

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
