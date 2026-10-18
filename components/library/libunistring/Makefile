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
# Copyright 2017 Aurelien Larcher
# Copyright 2019 Michal Nowak
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libunistring
COMPONENT_VERSION=	1.5
COMPONENT_SUMMARY=	libunistring - library for manipulating Unicode strings
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libunistring/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libunistring/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:fe89007a8a414ae4790b816b86859e877d3ab135db3c37f06541ff7e85ac344b
COMPONENT_FMRI=		library/libunistring
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPLv3, LGPLv3

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

COMPONENT_POST_INSTALL_ACTION += ( $(RM) $(PROTOUSRSHAREDIR)/info/dir );

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
