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
# Copyright 2022 Stephan Althaus
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		e2fsprogs
COMPONENT_VERSION=	1.46.5
COMPONENT_SUMMARY=	Second extended file system (ext2fs) management programs
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:2f16c9176704cf645dc69d5b15ff704ae722d665df38b2ed3cfc249757d8d81e
COMPONENT_ARCHIVE_URL= \
	https://www.kernel.org/pub/linux/kernel/people/tytso/e2fsprogs/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://e2fsprogs.sourceforge.net/
COMPONENT_FMRI=		sysutils/e2fsprogs
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	GPLv2

LIBUUID =  -luuid
STATIC_LIBUUID = -luuid
PROFILED_LIBUUID = -luuid

CONFIGURE_OPTIONS+=--enable-libblkid
CONFIGURE_OPTIONS+=--disable-libuuid
CONFIGURE_OPTIONS+=--enable-elf-shlibs
CONFIGURE_OPTIONS+=--enable-fsck=no
CONFIGURE_OPTIONS+=--without-pthread

COMPONENT_PRE_BUILD_ACTION = \
 patches/convert-Makefiles.sh $(@D)

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/prep-patch.mk
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
