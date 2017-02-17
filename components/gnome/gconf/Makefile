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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64_and_32
COMPILER =      	gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		GConf
COMPONENT_VERSION=	3.2.6
COMPONENT_PROJECT_URL=	https://projects.gnome.org/gconf/
COMPONENT_ARCHIVE_HASH=	\
    sha256:1912b91803ab09a5eed34d364bf09fe3a2a9c96751fde03a4e0cfa51a04d784c
COMPONENT_BUGDB=	gnome/libraries

TPNO=			26337

# While there is a tests subdirectory, it's not setup for automated use
# on a headless system, and isn't even built unless you manually do it.
TEST_TARGET = $(NO_TESTS)

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --disable-defaults-service
CONFIGURE_OPTIONS += --enable-gsettings_backend
CONFIGURE_OPTIONS += --disable-orbit
CONFIGURE_OPTIONS += --with-gtk=3.0
CONFIGURE_OPTIONS += --without-openldap
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# Need to convert "#! /usr/bin/env python" to actual path for pkgdepend to work
PYTHON_SCRIPTS += $(PROTO_DIR)$(CONFIGURE_BINDIR.$(BITS))/gsettings-schema-convert

PKG_MACROS += PYVER="$(PYTHON_VERSION)"

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/lxml-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/dbus/dbus-x11
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
