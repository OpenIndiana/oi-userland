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
COMPONENT_VERSION=	1.1
# Version was bumped in JDS
GIMP_GTKAM_VERSION=	2.30.0
COMPONENT_SUMMARY=	A GTK Digital Camera Viewing Tool
COMPONENT_PROJECT_URL=	http://libexif.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_ARCHIVE_HASH=	sha256:6832556bb603ce447fe4eee2b38458218786002280e77bf495640c723f2244fe
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gphoto/files/gtkam/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION= Applications/Graphics and Imaging
COMPONENT_FMRI= desktop/gtkam
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += GIMP_GTKAM_VERSION=$(GIMP_GTKAM_VERSION)

PATH= $(PATH.gnu)

CFLAGS += -Wno-error=implicit-function-declaration
CFLAGS += -Wno-error=incompatible-pointer-types

CONFIGURE_OPTIONS += --without-gnome
CONFIGURE_OPTIONS += --without-bonobo

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libexif-gtk
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgphoto2-2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
