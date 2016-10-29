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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-shell
COMPONENT_VERSION=	3.18.3
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/GnomeShell
COMPONENT_ARCHIVE_HASH= \
	sha256:8517baf8606f970ebf38222411eb7563cab2ae5efbfb088954ce23705b67519b
COMPONENT_BUGDB=        gnome/gnome-shell

TPNO=		25491

TEST_TARGET = $(NO_TESTS)

# Needs mutter, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# js/misc/config.js is accidentally included in the tarball - we remove it so
# that it gets correctly rebuilt from js/misc/config.js.in with the settings
# passed via the configure script
COMPONENT_POST_UNPACK_ACTION += $(RM) $(SOURCE_DIR)/js/misc/config.js ;

CXXFLAGS += -std=c++11 -D__EXTENSIONS__

PYTHON_VERSION= 3.4

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-man-pages
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --disable-networkmanager
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += PYTHON="$(PYTHON.$(PYTHON_VERSION))"

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH=$(GNUBIN):$(PATH)

# Workaround the mozjs issue described in 24935318
LD_EXEC_OPTIONS += -M $(PWD)/../gjs/mapfile
ADIHEAP_MODE = $(ADIHEAP_DISABLE)
ADISTACK_MODE =	$(ADISTACK_DISABLE)

# Delete this when build servers are installed with required packages
SN_TOP = $(WS_COMPONENTS)/desktop/startup-notification
SN_BASE = $(SN_TOP)/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(SN_BASE)$(PKG_CONFIG_PATH.$(BITS))
LD_OPTIONS += -L $(SN_BASE)$(USRLIB)
CPPFLAGS += -I$(SN_BASE)$(USRINCDIR)/startup-notification-1.0
DEPENDED += $(SN_TOP)/build/manifest-$(MACH)-startup-notification.depend
REQUIRED_PACKAGES += $(shell $(GSED) -n -e 's/REQUIRED_PACKAGES +=//p' $(SN_TOP)/Makefile)

MUTTER_BASE = $(WS_COMPONENTS)/gnome/mutter/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(MUTTER_BASE)$(PKG_CONFIG_PATH.$(BITS))
LD_OPTIONS += -L $(MUTTER_BASE)$(USRLIB)
CPPFLAGS += -I$(MUTTER_BASE)$(USRINCDIR)/mutter
CONFIGURE_ENV += INTROSPECTION_GIRDIR="$(MUTTER_BASE)/usr/lib/$(MACH64)/mutter"
MUTTER_GIRDIR=$(MUTTER_BASE)$(USRLIB)/mutter

EDS_BASE = $(WS_COMPONENTS)/gnome/evolution-data-server/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(EDS_BASE)$(PKG_CONFIG_PATH.$(BITS))
LD_OPTIONS += -L $(EDS_BASE)$(USRLIB)
CPPFLAGS += -I$(EDS_BASE)$(USRINCDIR)/evolution-data-server

COMPONENT_BUILD_ENV += LD_LIBRARY_PATH_64="$(GOA_BASE)/$(USRLIB):$(EDS_BASE)/$(USRLIB)/evolution-data-server:$(MUTTER_BASE)/$(USRLIB):$(BUILD_DIR_64)/src/.libs"

XDG_DATA_DIRS="$(MUTTER_GIR_DIR):$(CLUTTER_BASE)/usr/share/:/usr/share/"

COMPONENT_BUILD_ENV += XDG_DATA_DIRS="$(MUTTER_GIR_DIR):$(CLUTTER_BASE)/usr/share/:/usr/share/"
COMPONENT_BUILD_ENV += MUTTER_GIR_DIR="$(MUTTER_GIR_DIR):$(CLUTTER_BASE)/usr/share/:/usr/share/"

# Dependencies on other packages in this build not yet on build machines
UNINSTALLED_DEPS = gdm gnome-clocks gnome-settings-daemon libgweather
DEPENDED += $(UNINSTALLED_DEPS:%=../%/build/manifest-$(MACH)-*.depend)
REQUIRED_PACKAGES += $(shell $(GSED) -n -e '/GSED/d' -e 's/REQUIRED_PACKAGES += //p' $(UNINSTALLED_DEPS:%=../%/Makefile))
# end Delete

# evolution-data-server requires nss/nspr, but Solaris doesn't include a 64-bit
# pkg-config file for it, so we workaround this by using the one-off copy in the
# evolution-data-server component directory
PKG_CONFIG_PATHS += $(WS_COMPONENTS)/gnome/evolution-data-server

REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += gnome/accessibility/caribou
REQUIRED_PACKAGES += gnome/gnome-clocks
REQUIRED_PACKAGES += gnome/gnome-settings-daemon
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += gnome/window-manager/mutter
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/at-spi2-atk
REQUIRED_PACKAGES += library/desktop/at-spi2-core
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/evolution-data-server
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/geocode-glib
REQUIRED_PACKAGES += library/desktop/gjs
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libchamplain
REQUIRED_PACKAGES += library/desktop/libgee
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/folks
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/graphics/cogl
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libcroco
REQUIRED_PACKAGES += library/libical
REQUIRED_PACKAGES += library/libmozjs-24
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/python/pygobject-3-34
REQUIRED_PACKAGES += library/python/simplejson-34
REQUIRED_PACKAGES += library/telepathy-glib
REQUIRED_PACKAGES += library/telepathy-logger
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += system/display-manager/gdm
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/library/accountsservice
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/polkit
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxfixes
