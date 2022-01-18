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
# Copyright 2012, Jon Tibble
# Copyright 2017, Adam Stevko 
# Copyright 2022, Andreas Wacknitz
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mtr
COMPONENT_VERSION=	0.95
COMPONENT_FMRI=		diagnostic/mtr
COMPONENT_SUMMARY=	MTR - My Traceroute.  Diagnostic tool combining ping and traceroute.
COMPONENT_PROJECT_URL=	https://www.bitwizard.nl/mtr/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_ARCHIVE_HASH=	sha256:12490fb660ba5fb34df8c06a0f62b4f9cbd11a584fc3f6eceda0a99124e8596f
COMPONENT_ARCHIVE_URL=	https://github.com/traviscross/mtr/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

CFLAGS+= $(XPG6MODE)

COMPONENT_PREP_ACTION= ( cd $(@D); ./bootstrap.sh )

CONFIGURE_OPTIONS +=	--disable-dependency-tracking
CONFIGURE_OPTIONS +=	--without-gtk

unexport SHELLOPTS

# The provided tests all fail (propably because of missing privileges).
# Filter out noise:
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^make/d" ' \
	'-e "/CC/d" ' \
	'-e "/TESTS/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
