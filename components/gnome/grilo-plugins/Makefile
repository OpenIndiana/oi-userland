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
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		grilo-plugins
COMPONENT_VERSION=	0.2.16
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Grilo
COMPONENT_ARCHIVE_HASH= \
	sha256:80b4571f9db6df0d5f0873d30f2ee475204f5831d2974b89c58423d6ffac5203
COMPONENT_BUGDB=	gnome/multimedia

TPNO=			25380

# Tests dont work in the Userland framework yet
TEST_TARGET = $(SKIP_TEST)

# Needs gnome-online-accounts, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# For various non-standard #include extensions.
CFLAGS += -D__EXTENSIONS__

# Solaris doesn't have libdmap.
CONFIGURE_OPTIONS += --disable-dmap
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-goa
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/desktop/librest
REQUIRED_PACKAGES += library/desktop/search/tracker
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmime
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/desktop/gom
REQUIRED_PACKAGES += library/desktop/grilo
REQUIRED_PACKAGES += library/gnome/libmediaart
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/liboauth
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/network/avahi
