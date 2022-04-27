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
#BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fuse-ext2
COMPONENT_VERSION=	0.0.10
#COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Fuse-ext2 is an EXT2/EXT3/EXT4 filesystem for FUSE
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:ad2260df4ccfb8ba9f761c66ea7c3b24bf690eab46e6d562d2d2e5a5f2f76dff
COMPONENT_ARCHIVE_URL= \
	https://github.com/alperakcan/fuse-ext2/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/alperakcan/fuse-ext2
COMPONENT_FMRI=		library/fuse-ext2
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	gnu-gpl-v2

#GCC_VERSION= 10
#CFLAGS += -include semaphore.h 
CFLAGS += -include /usr/include/sys/fm/io/disk.h
LDFLAGS += -luuid -lcom_err -lpthread  
#-shared  -luuid -lcom_err -lpthread -llibext2fs

#COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )
COMPONENT_PREP_ACTION = ( cd $(@D) && ../fuse-ext2-0.0.10/autogen.sh )

CONFIGURE_OPTIONS+=--host=x86_64-pc-solaris2.11
#CONFIGURE_OPTIONS+=--host=i386-pc-solaris2.11

#COMPONENT_PRE_BUILD_ACTION = \
# patches/convert-Makefiles.sh $(@D)

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/prep-patch.mk
include $(WS_MAKE_RULES)/common.mk
# Auto-generated dependencies
REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += sysutils/e2fsprogs
