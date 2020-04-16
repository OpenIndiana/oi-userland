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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtkam
COMPONENT_VERSION=	1.0
COMPONENT_REVISION=	1
# Version was bumped in JDS
GIMP_GTKAM_VERSION=	2.30.0
COMPONENT_PROJECT_URL=	http://libexif.sourceforge.net/
COMPONENT_SUMMARY=	A GTK Digital Camera Viewing Tool
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:ab7f50d4654d129cd8b386658249b05ea739a446f08026c7352b829c63382c3d
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/gphoto/files/gtkam/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION = Applications/Graphics and Imaging
COMPONENT_FMRI = desktop/gtkam
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_MACROS += GIMP_GTKAM_VERSION=$(GIMP_GTKAM_VERSION)

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --without-gnome
CONFIGURE_OPTIONS += --without-bonobo

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += image/editor/gimp
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libexif-gtk
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgphoto2-2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
