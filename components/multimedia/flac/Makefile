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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		flac
COMPONENT_VERSION=	1.5.0
COMPONENT_SUMMARY=	An Open Source Lossless Audio Codec
COMPONENT_PROJECT_URL=	https://xiph.org/flac
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:f2c1c76592a82ffff8413ba3c4a1299b6c7ab06c734dee03fd88630485c2b920
COMPONENT_ARCHIVE_URL=	https://github.com/xiph/flac/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		codec/flac
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=	Xiph.org BSD-style, binaries & media player plugins also use GPL v2, LGPL v2.1, documentation uses FDL v1.2

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -fstack-protector-all
CFLAGS += $(XPG6MODE)

CONFIGURE_OPTIONS += --enable-ogg

ifeq   ($(MACH), i386)
CONFIGURE_OPTIONS += --enable-sse
ifeq   ($(BITS), 32)
CONFIGURE_OPTIONS += --enable-asm-optimizations
else
CONFIGURE_OPTIONS += --disable-asm-optimizations
endif
else
CONFIGURE_OPTIONS += --disable-sse
CONFIGURE_OPTIONS += --disable-asm-optimizations
endif

COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32)

# Note that the test needed to be run with standard user privileges.
COMPONENT_TEST_TRANSFORMS = \
	' -n ' \
	' -e "/unit test/p" ' \
	' -e "/---/p" ' \
	' -e "/passed/p" ' \
	' -e "/+++/p" ' \
	' -e "/PASSED/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
