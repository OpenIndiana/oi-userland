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
# Copyright 2020, 2024 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libass
COMPONENT_VERSION=	0.17.3
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Portable renderer for the ASS/SSA (Substation Alpha) subtitle format
COMPONENT_PROJECT_URL=	https://github.com/libass/libass
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:da7c348deb6fa6c24507afab2dee7545ba5dd5bbf90a137bfe9e738f7df68537
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/video/libass
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=	ISC
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# gcc 14 complains about incompatible pointer types
CFLAGS += -Wno-error=incompatible-pointer-types

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
ifeq ($(strip $(MACH)),i386)
CONFIGURE_OPTIONS.64 += --host=amd64-pc-solaris2.11
else
CONFIGURE_OPTIONS.64 += --host=sparcv9-sun-solaris2.11
endif

# build requirement
REQUIRED_PACKAGES += developer/assembler/nasm

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/libunibreak
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
