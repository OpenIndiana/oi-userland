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
# Copyright 2022 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lzlib
COMPONENT_VERSION=	1.14
COMPONENT_SUMMARY=	Lzlib is a data compression library providing in-memory LZMA compression and decompression functions
COMPONENT_PROJECT_URL=	https://lzip.nongnu.org/lzlib.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.lz
COMPONENT_ARCHIVE_HASH= sha256:e362ecccd82d4dd297df6a51b952c65d2172f9bf41a5c4590d3604d83aa519d3
COMPONENT_ARCHIVE_URL=	https://download.savannah.gnu.org/releases/lzip/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	BSD 2-clause
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

COMPONENT_TEST_TRANSFORMS += \
	'-n' \
	'-e "/test/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
