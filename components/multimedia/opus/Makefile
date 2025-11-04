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
# Copyright 2013 EveryCity Ltd. All rights reserved.
# Copyright 2016-2017 Aurelien Larcher. All rights reserved.
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			opus
COMPONENT_VERSION=		1.5.2
COMPONENT_SUMMARY=		Opus is an open, royalty-free, versatile audio codec for interactive speech and music transmission over the Internet
COMPONENT_PROJECT_URL=	https://opus-codec.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:65c1d2f78b9f2fb20082c38cbe47c951ad5839345876e46941612ee87f9a7ce1
COMPONENT_ARCHIVE_URL=	https://downloads.xiph.org/releases/opus/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/opus
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=		BSD-3-Clause
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk
PATH= $(PATH.gnu)

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
