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
# Copyright 2016 Till Wegmueller
# Copyright 2016 Ken Mays
# Copyright 2020 Michal Nowak
# Copyright (c) 2021 Tim Mooney.  All rights reserved
#

PREFERRED_BITS=		64
BUILD_BITS=		32_and_64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mate-menus
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	https://www.mate-desktop.org
COMPONENT_SUMMARY=	The Menu of Mate
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:0309964abd813053368ac4fc446898d27cdb019e894e78cea75751a68871ffe4
COMPONENT_ARCHIVE_URL=	https://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=		library/desktop/mate/$(COMPONENT_NAME)

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)
GNUCP = /usr/gnu/bin/cp

COMPONENT_PREP_ACTION=	cd $(@D) && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))/mate
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Build dependencies
REQUIRED_PACKAGES += library/desktop/mate/mate-common

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
