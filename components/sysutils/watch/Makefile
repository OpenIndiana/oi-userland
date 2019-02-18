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

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		watch
COMPONENT_VERSION=	3.3.15
COMPONENT_SUMMARY=	The Linux watch utility
COMPONENT_PROJECT_URL=	https://gitlab.com/procps-ng/procps
COMPONENT_FMRI=		utilities/watch
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		procps-ng-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/procps-ng/Production/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:10bd744ffcb3de2d591d2f6acf1a54a7ba070fdcc432a855931a5057149f0465
COMPONENT_LICENSE=	GPL-2.0-or-later, LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f -i)

# Disable optional utilities
CONFIGURE_OPTIONS +=	--disable-pidof
CONFIGURE_OPTIONS +=	--disable-kill
CONFIGURE_OPTIONS +=	--disable-modern-top
CONFIGURE_OPTIONS +=	--disable-numa
CONFIGURE_OPTIONS +=	--enable-watch8bit

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
