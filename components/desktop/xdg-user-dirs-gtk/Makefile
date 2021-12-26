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

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdg-user-dirs-gtk
COMPONENT_VERSION=	0.10
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_SUMMARY=	Tool to help manage user directories
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:739a1a89baf34aa7261e924a21d2ae646b0475b67b3db3daa84327a99132d83e
COMPONENT_ARCHIVE_URL=	https://ftp.gnome.org/pub/gnome/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI=		desktop/xdg/xdg-user-dirs-gtk

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/xdg/xdg-user-dirs
REQUIRED_PACKAGES += system/library
