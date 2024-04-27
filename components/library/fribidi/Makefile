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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 64_and_32
USE_COMMON_TEST_MASTER= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fribidi
COMPONENT_VERSION=	1.0.14
COMPONENT_SUMMARY=	Free Implementation of the Unicode Bidirectional Algorithm
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:76ae204a7027652ac3981b9fa5817c083ba23114340284c58e756b259cd2259a
COMPONENT_PROJECT_URL=	https://github.com/fribidi/fribidi
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/fribidi
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --disable-dependency-tracking

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
