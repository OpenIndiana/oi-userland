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
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-settings-daemon
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	http://wiki.gnome.org
COMPONENT_ARCHIVE_HASH= \
	sha256:8d3ef9c18538831ed89122fee0bdaca68b0e482a18b3c4388c4e672aba1b3cd5
COMPONENT_BUGDB=	gnome/session
COMPONENT_ANITYA_ID=	12860

TPNO=			24901

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Use the GNOME 3 libnotify even though the GNOME 2 one is still the default
PKG_CONFIG_PATHS.32 += /usr/lib/pkgconfig/libnotify-4
PKG_CONFIG_PATHS.64 += /usr/lib/$(MACH64)/pkgconfig/libnotify-4
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L /usr/lib/libnotify-4 -R /usr/lib/libnotify-4
LD_OPTIONS.64 += -L /usr/lib/$(MACH64)/libnotify-4 -R /usr/lib/$(MACH64)/libnotify-4
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

# A pkg-config file isn't shipped in Solaris for nss/nspr 64-bit, so we
# workaround this by using the one-off copy in the evolution-data-server
# component directory
PKG_CONFIG_PATHS.64 += $(WS_COMPONENTS)/gnome/evolution-data-server

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# gudev not yet supported on Solaris.
CONFIGURE_OPTIONS += --disable-gudev
# GNOME NetworkManager not yet supported on Solaris.
CONFIGURE_OPTIONS += --disable-network-manager
# Linux-specific.
CONFIGURE_OPTIONS += --disable-rfkill
CONFIGURE_OPTIONS += --disable-static
# Wayland not yet supported on Solaris.
CONFIGURE_OPTIONS += --disable-wayland
CONFIGURE_OPTIONS += --enable-man
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/geoclue
REQUIRED_PACKAGES += library/desktop/geocode-glib
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/nss
REQUIRED_PACKAGES += service/image/colord
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/polkit
REQUIRED_PACKAGES += system/library/upower
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxtst
