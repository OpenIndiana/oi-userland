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
BUILD_BITS= 		64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER= 		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gdm
COMPONENT_VERSION=	3.18.2
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/GDM
COMPONENT_ARCHIVE_HASH= \
	sha256:549235247611d74f0d5d5a4aa01ba9350a4d3468e44ac013b40791c6a986f822
COMPONENT_BUGDB=        gnome/gdm

TPNO=			25845

# Needs accountsservice, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Regenerate configure after patches modify configure.ac
COMPONENT_PREP_ACTION += ( cd $(@D); autoreconf -fiv);

# Make sure we haven't broken the SMF manifest formatting
COMPONENT_PREP_ACTION += \
    ( /usr/sbin/svccfg validate $(COMPONENT_DIR)/files/gdm.xml );

# Assumes GNU msgfmt in PATH.
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

# uuid detection fails due to Solaris bug 15586738.
CONFIGURE_OPTIONS += ac_cv_search_uuid_to_string=generic
CONFIGURE_ENV += UUID_CFLAGS="-I$(USRINCDIR)/uuid"
CONFIGURE_ENV.32 += UUID_LIBS="-luuid"
CONFIGURE_ENV.64 += UUID_LIBS="-L$(USRLIBDIR64) -luuid"

# intltool may or may not be run depending on previous state of build dir
COMPONENT_TEST_TRANSFORMS += "-e '/\/usr\/bin\/intltool-update/d'"

CONFIGURE_OPTIONS += --enable-debug
CONFIGURE_OPTIONS += --enable-authentication-scheme=pam
CONFIGURE_OPTIONS += --enable-gdm-xsession
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-rbac-shutdown=solaris.system.shutdown
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-systemd-journal
CONFIGURE_OPTIONS += --disable-wayland-support
CONFIGURE_OPTIONS += --with-console-kit
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --without-plymouth
CONFIGURE_OPTIONS += --without-systemd
CONFIGURE_OPTIONS += --without-systemdsystemunitdir
CONFIGURE_OPTIONS += --with-user=gdm --with-group=gdm
CONFIGURE_OPTIONS += --with-default-path='$(USRBINDIR):$(USRSBINDIR)'
CONFIGURE_OPTIONS += --with-xauth-dir=/tmp
CONFIGURE_OPTIONS += --with-initial-vt=7
CONFIGURE_OPTIONS += --libexecdir="$(USRLIBDIR)/gdm"

REQUIRED_PACKAGES += data/iso-codes
REQUIRED_PACKAGES += developer/documentation-tool/itstool
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += gnome/accessibility/orca
REQUIRED_PACKAGES += gnome/gnome-session
REQUIRED_PACKAGES += gnome/gnome-shell
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += gnome/zenity
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/dconf
REQUIRED_PACKAGES += library/gnome/yelp-tools
REQUIRED_PACKAGES += library/xdg/consolekit
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/input-method/imf-startup
REQUIRED_PACKAGES += system/io/audio
REQUIRED_PACKAGES += system/library/accountsservice
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += terminal/xterm
REQUIRED_PACKAGES += x11/keyboard/xkb-utilities
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxdmcp
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/server/xephyr
REQUIRED_PACKAGES += x11/server/xserver-common
REQUIRED_PACKAGES += x11/session/xinit
REQUIRED_PACKAGES += x11/x11-server-utilities

# Required for testing, not building or running:
REQUIRED_PACKAGES += developer/test/check
REQUIRED_PACKAGES += library/libxml2
