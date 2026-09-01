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
# Copyright 2019 Michal Nowak
#

BUILD_BITS=			64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		watch
COMPONENT_VERSION=	4.0.7
COMPONENT_SUMMARY=	Execute a program repeatedly, displaying output fullscreen
COMPONENT_PROJECT_URL=	https://gitlab.com/procps-ng/procps
COMPONENT_FMRI=		utilities/watch
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		procps-ng-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/procps-ng/Production/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:9d2021f47a4501c667862c9942a92d1953694b21d11bcd1702e83eb594e3d67d
COMPONENT_LICENSE=	GPL-2.0-or-later, LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f -i)

# Disable optional utilities
CONFIGURE_OPTIONS +=	--disable-kill
CONFIGURE_OPTIONS +=	--disable-modern-top
CONFIGURE_OPTIONS +=	--disable-numa
CONFIGURE_OPTIONS +=	--disable-pidof
CONFIGURE_OPTIONS +=	--disable-pidwait
CONFIGURE_OPTIONS +=	--disable-skill
CONFIGURE_OPTIONS +=	--disable-w
CONFIGURE_OPTIONS +=	--enable-colorwatch
# is needed to be able to build.
CONFIGURE_OPTIONS +=	--disable-dependency-tracking

COMPONENT_BUILD_ARGS=src/watch

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
