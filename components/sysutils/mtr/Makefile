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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mtr
COMPONENT_VERSION=	0.96
COMPONENT_SUMMARY=	MTR - My Traceroute.  Diagnostic tool combining ping and traceroute.
COMPONENT_PROJECT_URL=	https://www.bitwizard.nl/mtr/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:73e6aef3fb6c8b482acb5b5e2b8fa7794045c4f2420276f035ce76c5beae632d
COMPONENT_ARCHIVE_URL=	https://github.com/traviscross/mtr/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		diagnostic/mtr
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS+= $(XPG6MODE)

COMPONENT_PREP_ACTION= ( cd $(@D); ./bootstrap.sh )

CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --without-gtk

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
