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
# Copyright 2022 Gary Mills
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

# requires gobject-introspection

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libpeas
COMPONENT_SUMMARY=	A gobject-based plugins engine for GNOME
COMPONENT_DESCRIPTION=	libpeas is a gobject-based plugins engine, and is targeted\
 at giving every application the chance to assume its own extensibility.
COMPONENT_VERSION=	1.20.0
COMPONENT_REVISION=	5
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/Libpeas
COMPONENT_MAJOR_MINOR=        $(basename $(COMPONENT_VERSION))
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=        https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_MINOR)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
	sha256:f392fffe2dc00072a51bb2a1b274224a06bdc5f9c3b3c0ac4816909e9933d354
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_FMRI=	library/desktop/libpeas
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += PYTHON=$(PYTHON)
CONFIGURE_ENV += PYTHON3_CONFIG=/usr/bin/python$(PYTHON_VERSION)-config

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk
CONFIGURE_OPTIONS += --enable-lua5.2
CONFIGURE_OPTIONS += --disable-luajit
CONFIGURE_OPTIONS += --disable-python2
CONFIGURE_OPTIONS += --enable-python3
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

# Assumes GNU xgettext in PATH
PATH = $(PATH.gnu)

# gobject introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); PATH="$(PATH)" autoreconf -fiv);

# for the tests
unexport SHELLOPTS
COMPONENT_TEST_ARGS =   -k -i
# Strip pids from test output, since they're always different
COMPONENT_TEST_TRANSFORMS += '-e "s% (pid=[0-9]*)%%"'
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TEST:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" '

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pygobject-3
REQUIRED_PACKAGES += developer/ui-designer/glade
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/lua/lgi-52
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
