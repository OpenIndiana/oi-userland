##
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         hicolor-icon-theme
COMPONENT_VERSION=      0.17
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://freedesktop.org/wiki/Software/icon-theme/
COMPONENT_SUMMARY=      GNOME Hi Color Icon Theme
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:317484352271d18cbbcfac3868eab798d67fff1b8402e740baa6ff41d588a9d8
COMPONENT_ARCHIVE_URL=  https://icon-theme.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_FMRI=	gnome/theme/hicolor-icon-theme
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc