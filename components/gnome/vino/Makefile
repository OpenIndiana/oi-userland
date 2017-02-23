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

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vino
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Vino
COMPONENT_ARCHIVE_HASH= \
	sha256:52be0b036389713eab224abf27f2ca2a067ba5bd1f6b526592703576005e0919
COMPONENT_BUGDB=        gnome/remote-desktop
COMPONENT_ANITYA_ID=	5572

TPNO=			24888

TEST_TARGET = $(NO_TESTS)

# Needs updated glib2, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATHS.32 += $(PKG_CONFIG_PATH.32)/gnutls-3
PKG_CONFIG_PATHS.64 += $(PKG_CONFIG_PATH.64)/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L $(USRLIB.32)/gnutls-3 -R $(USRLIB.32)/gnutls-3
LD_OPTIONS.64 += -L $(USRLIB.64)/gnutls-3 -R $(USRLIB.64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

PKG_CONFIG_PATHS.32 += $(PKG_CONFIG_PATH.32)/libnotify-4
PKG_CONFIG_PATHS.64 += $(PKG_CONFIG_PATH.64)/libnotify-4
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L $(USRLIB.32)/libnotify-4 -R $(USRLIB.32)/libnotify-4
LD_OPTIONS.64 += -L $(USRLIB.64)/libnotify-4 -R $(USRLIB.64)/libnotify-4
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-avahi
CONFIGURE_OPTIONS += --with-gcrypt
CONFIGURE_OPTIONS += --with-gnutls
CONFIGURE_OPTIONS += --with-jpeg
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-secret
CONFIGURE_OPTIONS += --with-telepathy
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/telepathy-glib
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxtst
