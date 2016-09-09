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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-system-monitor
COMPONENT_VERSION=	3.18.0.1
COMPONENT_PROJECT_URL=  https://help.gnome.org/users/gnome-system-monitor/
COMPONENT_ARCHIVE_HASH= \
	sha256:71ff8db2fa3eb53d8f54ffd612c6679b231a9d69c13adb91cf63421425953b10
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/3.18/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        gnome/applications

TPNO=			24894

# Needs updated glib2, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

CFLAGS += -std=c11
CXXFLAGS += -std=c++11
# Uses gcc-specific language extensions.
CXXFLAGS.studio += -features=extensions

CONFIGURE_OPTIONS += --disable-static
# Linux-specific.
CONFIGURE_OPTIONS += --disable-systemd
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-wnck
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --libexecdir="$(USRLIBDIR)"

# Assumes GNU msgfmt is in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm3
REQUIRED_PACKAGES += library/desktop/c++/mm-common
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libwnck3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgtop
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
