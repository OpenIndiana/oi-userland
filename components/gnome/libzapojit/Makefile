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

COMPONENT_NAME=		libzapojit
COMPONENT_VERSION=	0.0.3
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Zapojit
COMPONENT_ARCHIVE_HASH=	\
	sha256:3d25f99329105abb99d1e9651b0aa1842065456ea54c22970a7330e9f3d1c37e
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25454

TEST_TARGET = $(NO_TESTS)

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk-doc
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

# Expects GNU utilities in path (e.g. GNU cp, etc.)
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# Delete once builds servers have goa installed
GOA_BASE = $(WS_COMPONENTS)/gnome/gnome-online-accounts/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(GOA_BASE)/usr/lib/$(MACH64)/pkgconfig

LD_OPTIONS += -L $(GOA_BASE)$(USRLIB.$(BITS))

CPPFLAGS +=  \
	-I$(GOA_BASE)/usr/include/goa-1.0 \
	-I$(GOA_BASE)/usr/lib/$(MACH64)/goa-1.0/include

COMPONENT_BUILD_ENV += LD_LIBRARY_PATH_64="$(GOA_BASE)/$(USRLIB.$(BITS)):$(BUILD_DIR_64)/src/.libs"

# The dependency isn't installed, so add it manually since pkgdepend
# can't resolve them yet: 15708323
DEPENDED += $(WS_TOP)/components/gnome/gnome-online-accounts/build/manifest-$(MACH)-gnome-online-accounts.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../gnome-online-accounts/Makefile)
#end Delete

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/librest
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libsoup
