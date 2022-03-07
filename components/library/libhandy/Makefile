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
BUILD_STYLE=meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libhandy
COMPONENT_VERSION=      1.5.90
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://gitlab.gnome.org/GNOME/libhandy
COMPONENT_SUMMARY=      Library full of GTK+ widgets for mobile phones
COMPONENT_FMRI=         library/libhandy
COMPONENT_SRC=          libhandy-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:69c137b5782293539371bcdbd15b91cc1f0f4a2f54d9bde3b3398607a58890a2
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.5/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= libhandy.license

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/ui-designer/glade
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
