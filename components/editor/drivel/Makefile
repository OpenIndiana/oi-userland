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
# Copyright 2017 Alexander Pyhalov
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         drivel
COMPONENT_VERSION=      3.0.5
COMPONENT_REVISION=     5
COMPONENT_PROJECT_URL=  http://drivel.sourceforge.net/
COMPONENT_SUMMARY=      Drivel is a GNOME client for editing blog
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:71b4af2552c22124a20e0b40958103f41beb3cb591b7b7e0c184e2817554a3fb
COMPONENT_ARCHIVE_URL=  http://prdownloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         editor/blog/drivel
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=      GPLv2

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS+= -std=gnu89 -D__EXTENSIONS__

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV += 	LIBS=-lm

# SPARC needs math library.
REQUIRED_PACKAGES += system/library/math

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtksourceview
REQUIRED_PACKAGES += library/desktop/gtkspell
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-vfs
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
