#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk
BUILD_STYLE= meson
BUILD_BITS= 32_and_64

COMPONENT_NAME= gdk-pixbuf-xlib
COMPMAJOR= 2.40
COMPMINOR= 2
COMPONENT_VERSION= $(COMPMAJOR).$(COMPMINOR)
COMPONENT_SUMMARY= GNOME gdk-pixbuf-xlib
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPMAJOR).$(COMPMINOR)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:8b8e1c270ec16a06f665ea841f8e4e167eaa0118d0cbfeeade43745f09198ff7
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPMAJOR)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://gitlab.gnome.org/Archive/gdk-pixbuf-xlib
COMPONENT_FMRI=	library/desktop/gdk-pixbuf-xlib

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
