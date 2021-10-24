#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2021 Andreas Wacknitz
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xapian
COMPONENT_VERSION=	1.4.18
COMPONENT_PROJECT_URL=	https://xapian.org
COMPONENT_SUMMARY=	An Open Source Search Engine Library
COMPONENT_SRC=		$(COMPONENT_NAME)-core-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:196ddbb4ad10450100f0991a599e4ed944cbad92e4a6fe813be6dce160244b77
COMPONENT_ARCHIVE_URL=	https://oligarchy.co.uk/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2+
COMPONENT_FMRI=		library/xapian
COMPONENT_CLASSIFICATION=	System/Libraries

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION =	( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

COMPONENT_TEST_TRANSFORMS += \
	'-n' \
	'-e "/^Running /p"' \
	'-e "/^PASS/p"' \
	'-e "/failed/p"' \
	'-e "/^Please/p"' \
	'-e "/======/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
