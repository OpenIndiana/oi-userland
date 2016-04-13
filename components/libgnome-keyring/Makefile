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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgnome-keyring
COMPONENT_VERSION=	2.32.0
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	GNOME keyring libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:56388c0d81ddfdb57d30e4963c83ecc1c18498aab99395420e0fff69929a0f0c
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_FMRI=		library/gnome/gnome-keyring
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS.32=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS.64=	--libexecdir=/usr/lib/$(MACH64)

CONFIGURE_OPTIONS+=	$(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
