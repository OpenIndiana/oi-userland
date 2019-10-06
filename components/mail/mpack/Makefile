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
# Copyright 2019 Nona Hansel
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mpack
COMPONENT_VERSION=	1.6
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	utilities for encoding and decoding (respectively) binary files in MIME format mail messages 
COMPONENT_PROJECT_URL=	ftp://ftp.andrew.cmu.edu:pub/mpack
COMPONENT_FMRI=		mail/mpack
COMPONENT_CLASSIFICATION= System/Text Tools	
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://fossies.org/linux/misc/old/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
	sha256:274108bb3a39982a4efc14fb3a65298e66c8e71367c3dabf49338162d207a94c
COMPONENT_LICENSE=	CMU

PATCH_LEVEL=		0

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Some source files are read-only
COMPONENT_POST_UNPACK_ACTION= $(CHMOD) +w $(SOURCE_DIR)/*

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS+= --mandir=/usr/share/man
CONFIGURE_OPTIONS+= --bindir=/usr/bin

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
