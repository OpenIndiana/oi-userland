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

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zenity
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Zenity
COMPONENT_ARCHIVE_HASH= \
	sha256:0efafea95a830f3bf6eca805ff4a8008df760a6ad3e81181b9473dcf721c3a69

TPNO=			24606

# zenity is not unlockable in S11 gnome-incorporation
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# Use the GNOME 3 libnotify even though the GNOME 2 one is still the default
PKG_CONFIG_PATHS.32 += $(PKG_CONFIG_PATH.32)/libnotify-4
PKG_CONFIG_PATHS.64 += $(PKG_CONFIG_PATH.64)/libnotify-4
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L $(USRLIB.32)/libnotify-4 -R $(USRLIB.32)/libnotify-4
LD_OPTIONS.64 += -L $(USRLIB.64)/libnotify-4 -R $(USRLIB.64)/libnotify-4
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

# Ensures gdialog script specifies explicit version of perl.
CONFIGURE_ENV += PERL="$(PERL)"

CONFIGURE_OPTIONS += --enable-libnotify
CONFIGURE_OPTIONS += --enable-webkitgtk

# Assumes GNU msgfmt in PATH.
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk4
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += x11/library/libx11
