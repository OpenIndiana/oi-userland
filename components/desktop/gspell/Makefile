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
# Copyright 2022 Niklas Poslovski
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gspell
COMPONENT_VERSION=      1.9.1
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/gspell
COMPONENT_SUMMARY=      A flexible API to implement the spell checking in a GTK+ application
COMPONENT_FMRI=         library/desktop/gspell
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:dcbb769dfdde8e3c0a8ed3102ce7e661abbf7ddf85df08b29915e92cd723abdd
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.9/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= gspell.license

CONFIGURE_OPTIONS += MAKE=gmake

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
