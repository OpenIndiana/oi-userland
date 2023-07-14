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
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libunistring
COMPONENT_VERSION=	1.0
COMPONENT_REVISION=	2
COMPONENT_FMRI=		library/libunistring
COMPONENT_SUMMARY=	libunistring - library for manipulating Unicode strings
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libunistring/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libunistring/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:5bab55b49f75d77ed26b257997e919b693f29fd4a1bc22e0e6e024c246c72741
COMPONENT_LICENSE=	GPLv3, LGPLv3

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

# Prevent test failures
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
 	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
