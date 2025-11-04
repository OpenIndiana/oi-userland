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
# Copyright 2024 Geoff Weiss
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

# Odd minor versions are unstable.
# More details at:
# https://blog.gtk.org/2016/09/01/versioning-and-long-term-stability-promise-in-gtk/

COMPONENT_NAME =		gtk
HUMAN_VERSION =			4.16.13
COMPONENT_SUMMARY =		The GTK toolkit
COMPONENT_ARCHIVE_HASH =	\
	sha256:ddf3d9e12b848139a945d191d5ca56b78d0647f53b55b8bca5f9902b61624498
COMPONENT_PROJECT_URL =		https://www.gtk.org/
COMPONENT_FMRI =		library/desktop/gtk4
COMPONENT_CLASSIFICATION =	Desktop (GNOME)/Libraries
COMPONENT_LICENSE =		LGPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH=$(PATH.gnu)

# needed to produce /usr/lib/amd64/girepository-1.0 files
CONFIGURE_OPTIONS += -Dintrospection=enabled

CONFIGURE_OPTIONS += -Dman-pages=true
# requires encumbered x264 support
CONFIGURE_OPTIONS += -Dmedia-gstreamer=disabled
CONFIGURE_OPTIONS += -Dwayland-backend=false

# We have no vulkan support
CONFIGURE_OPTIONS += -Dvulkan=disabled

# Note that the number of failing tests vary for unknown reasons between runs
#
# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :1 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:1
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

#
# Installed gtk4 libraries are causing many tests to fail and we didn't found a
# way how to prevent their loading.  There are basically these libraries
# causing problems:
#
# 1) libgtk-4.so - to avoid loading of the system installed libgtk we can do
#    this:
#
#	COMPONENT_TEST_ENV += LD_LIBRARY_PATH=gtk
#
#    but since we force the library/desktop/gtk4 uninstall we do not do that.
#
# 2) libraries in /usr/lib/amd64/gtk-4.0/4.0.0/printbackends/ - we have found
#    no way how to prevent their loading, except by removing them.
#
TEST_CONFLICTING_PACKAGES += library/desktop/gtk4

# Dynamic library version number
SOVER := 1.$(shell printf '%s00.%s' $(wordlist 2,3,$(subst ., ,$(COMPONENT_VERSION))))
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Build dependencies
REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
