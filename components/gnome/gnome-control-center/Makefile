#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-control-center
COMPONENT_VERSION=	3.18.2
COMPONENT_PROJECT_URL=  https://git.gnome.org/browse/gnome-control-center
COMPONENT_ARCHIVE_HASH= \
	sha256:36fe6157247d2b7c8a98dbb3dbcde1c3a6f9e5e8fcc9ccf357e2b2417578f8ad
COMPONENT_BUGDB=	gnome/preferences

TPNO=			25823

TEST_TARGET = $(NO_TESTS)

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --disable-cups
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-update-mimedb
CONFIGURE_OPTIONS += --enable-documentation
CONFIGURE_OPTIONS += --enable-ibus
# Required for other components.
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-x
# No webcam support.
CONFIGURE_OPTIONS += --without-cheese

# Needed due to patch to configure.ac.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

# Use the GNOME 3 libnotify even though the GNOME 2 one is still the default
PKG_CONFIG_PATHS.32 += /usr/lib/pkgconfig/libnotify-4
PKG_CONFIG_PATHS.64 += /usr/lib/$(MACH64)/pkgconfig/libnotify-4
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L /usr/lib/libnotify-4 -R /usr/lib/libnotify-4
LD_OPTIONS.64 += -L /usr/lib/$(MACH64)/libnotify-4 -R /usr/lib/$(MACH64)/libnotify-4
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

REQUIRED_PACKAGES += gnome/gnome-settings-daemon
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/colord-gtk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/grilo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/libgtop
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += service/image/colord
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/library/accountsservice
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/libv12n
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/polkit
REQUIRED_PACKAGES += system/library/upower
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/mesa
