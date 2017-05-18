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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mtr
COMPONENT_VERSION=	0.87
COMPONENT_FMRI=		diagnostic/mtr
COMPONENT_SUMMARY=	MTR - My Traceroute.  Diagnostic tool combining ping and traceroute.
COMPONENT_PROJECT_URL=	http://www.bitwizard.nl/mtr/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_ARCHIVE_HASH=	sha256:193947c61d23b154c8dc03677e90e8fd912f8f18567ab76ce619b7856c4af19f
COMPONENT_ARCHIVE_URL=	ftp://ftp.bitwizard.nl/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_SBINDIR.64 = $(CONFIGURE_SBINDIR.32)

CONFIGURE_OPTIONS+=	--without-gtk

build:		$(BUILD_64)

install:	$(INSTALL_64)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
