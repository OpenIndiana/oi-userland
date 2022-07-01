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
# Copyright 2019 Michal Nowak
# Copyright 2020, 2021 Andreas Wacknitz
#
BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libass
COMPONENT_VERSION=	0.16.0
COMPONENT_FMRI=		library/video/libass
COMPONENT_SUMMARY=	Portable renderer for the ASS/SSA (Substation Alpha) subtitle format
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:fea8019b1887cab9ab00c1e58614b4ec2b1cee339b3f7e446f5fab01b032d430
COMPONENT_ARCHIVE_URL=	https://github.com/libass/libass/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/libass/libass
COMPONENT_LICENSE=	ISC

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS.64 += --host=amd64-pc-solaris2.11
CONFIGURE_OPTIONS.32 += --host=i686-pc-solaris2.11

# build requirement
REQUIRED_PACKAGES += developer/assembler/nasm
# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
