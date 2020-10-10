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
# Copyright 2018 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS=				64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			adwaita-icon-theme
COMPONENT_MJR_VERSION=	3.38
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=		$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/GNOME/adwaita-icon-theme
COMPONENT_SUMMARY=		GNOME Icon Theme
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:6683a1aaf2430ccd9ea638dd4bfe1002bc92b412050c3dba20e480f979faaf97
COMPONENT_ARCHIVE_URL=	https://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			gnome/theme/adwaita-icon-theme

TEST_TARGET=			$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += library/desktop/xdg/icon-naming-utils
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf

# Auto-generated dependencies
