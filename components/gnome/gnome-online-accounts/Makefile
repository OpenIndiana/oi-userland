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

COMPONENT_NAME=		gnome-online-accounts
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/GnomeOnlineAccounts
COMPONENT_ARCHIVE_HASH= \
	sha256:fc2dac96551746576759bd14f9b322bae1dd0aeedc0e755065ddf5eaaefacd34
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25358

TEST_TARGET = $(NO_TESTS)

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# Doesn't build currently; conflicts between Solaris krb5.h and p11-kit.
CONFIGURE_OPTIONS += --disable-kerberos
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-exchange
CONFIGURE_OPTIONS += --enable-documentation
CONFIGURE_OPTIONS += --enable-gtk-doc
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-facebook
CONFIGURE_OPTIONS += --enable-flickr
CONFIGURE_OPTIONS += --enable-google
CONFIGURE_OPTIONS += --enable-imap-smtp
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-telepathy
CONFIGURE_OPTIONS += --enable-windows-live
CONFIGURE_OPTIONS += --with-pic

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/librest
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk4
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/telepathy-glib
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
