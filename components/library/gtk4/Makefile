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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gtk
HUMAN_VERSION =			4.16.1
COMPONENT_SUMMARY =		The GTK toolkit
COMPONENT_ARCHIVE_HASH =	\
	sha256:926a1eabd481f9bfa25538f95016fdfcfaf963b2f90b40ae69e90def5499215c
COMPONENT_PROJECT_URL =		https://www.gtk.org/
COMPONENT_FMRI =		library/desktop/gtk4
COMPONENT_CLASSIFICATION =	Desktop (GNOME)/Libraries
COMPONENT_LICENSE =		LGPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Uses isinf, etc. only available in c99 and newer
CFLAGS.gcc += -std=gnu11

#needed to produce /usr/lib/amd64/girepository-1.0 files
CONFIGURE_OPTIONS += -Dintrospection=enabled

CONFIGURE_OPTIONS += -Dman-pages=true
# requires encumbered x264 support
CONFIGURE_OPTIONS += -Dmedia-gstreamer=disabled
CONFIGURE_OPTIONS += -Dwayland-backend=false

# We have no vulkan support
CONFIGURE_OPTIONS += -Dvulkan=disabled

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Remove the empty line after the 'Summary of Failures:'
COMPONENT_TEST_TRANSFORMS += "-e '/^Summary of Failures:/{n; N; D; }' | $(COMPONENT_TEST_TRANSFORMER)"
# Remove the list of failed tests so we do not see the failed tests twice
COMPONENT_TEST_TRANSFORMS += "-e '/^Summary of Failures:/,/^\$$/d'"
# By default ignore all lines
COMPONENT_TEST_TRANSFORMS += "-n"
# Print the individual test result with removed test number and timing
COMPONENT_TEST_TRANSFORMS += "-e '/^ *[0-9]\{1,\}\/[0-9]\{1,\} /{s///; s/ \{1,\}[0-9]*[0-9]\.[0-9][0-9]s//; p; }'"
# Print the test summary too
COMPONENT_TEST_TRANSFORMS += "-e '/^Ok:/,/^\$$/p'"
# Include empty line before the test summary
COMPONENT_TEST_TRANSFORMS += "| $(COMPONENT_TEST_TRANSFORMER) -e '/^Ok:/{H; x; }'"
# Sort test results
COMPONENT_TEST_TRANSFORMS += "| ( \
		$(GSED) -u -e '/^\$$/Q' | $(SORT) | $(COMPONENT_TEST_TRANSFORMER) -e '\$$G' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

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

# Build dependencies
REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libjpeg-turbo
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
