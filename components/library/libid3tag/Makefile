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
# Copyright 2015 Alexander Pyhalov
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libid3tag
COMPONENT_VERSION=	0.16.3
COMPONENT_SUMMARY=	ID3 tag reading library from the MAD project
COMPONENT_PROJECT_URL=	https://www.underbit.com/products/mad/
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0561009778513a95d91dac33cee8418d6622f710450a7cb56a74636d53b588cb
COMPONENT_ARCHIVE_URL=	https://codeberg.org/tenacityteam/libid3tag/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/audio/libid3tag
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

FP_ARCH.32 = default
FP_ARCH.64 = 64bit

CONFIGURE_OPTIONS  += --sysconfdir=/etc
CONFIGURE_OPTIONS  += --enable-shared
CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  += --enable-accuracy
CONFIGURE_OPTIONS  += --enable-fpm=$(FP_ARCH.$(BITS))

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
