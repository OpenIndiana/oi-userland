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
# Copyright (c) 2023 Friedrich Kink
# Copyright (c) 2024 Andreas Wacknitz
#

BUILD_BITS= 64
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgnome-keyring
COMPONENT_VERSION_MJR=	3.12
COMPONENT_VERSION=	$(COMPONENT_VERSION_MJR).0
COMPONENT_SUMMARY=	GNOME keyring libraries
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:c4c178fbb05f72acc484d22ddb0568f7532c409b0a13e06513ff54b91e947783
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MJR)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_FMRI=		library/gnome/gnome-keyring
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --libexecdir=$(LIBEXECDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --disable-static

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Manually added build dependencies
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/security/libgcrypt
