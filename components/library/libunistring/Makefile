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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libunistring
COMPONENT_VERSION=	1.1
COMPONENT_SUMMARY=	libunistring - library for manipulating Unicode strings
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libunistring/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libunistring/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:827c1eb9cb6e7c738b171745dac0888aa58c5924df2e59239318383de0729b98
COMPONENT_FMRI=		library/libunistring
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPLv3, LGPLv3

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

# Prevent test failures
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
