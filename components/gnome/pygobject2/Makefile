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

# gobject-introspection bindings are only built correctly for gtk when building
# with gcc, this would otherwise build with Studio.
COMPILER =		gcc
BUILD_BITS =		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pygobject
COMPONENT_VERSION=	2.28.6
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/PyGObject
COMPONENT_ARCHIVE_HASH= \
	sha256:fb8a1d4f665130a125011659bd347c7339c944232163dbb9a34fd0686577adb8
COMPONENT_BUGDB=       gnome/libraries
COMPONENT_ANITYA_ID=	13158

TPNO=			19934

# Only build for 2.7 as python 3.x support is provided by ../pygobject3 instead
PYTHON_VERSIONS= 2.7

# Tests do not yet work with Userland framework - 23712631
TEST_TARGET= $(SKIP_TEST)
include $(WS_MAKE_RULES)/gnome-component.mk

# Needed due to patches/01-pyexecsubdir.patch modifying Makefile.am files
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

CONFIGURE_OPTIONS += --disable-static

# Disable introspection modules in this package since we ship the modern ones
# in the ../pygobject3 packages instead, and they'd clash if we didn't disable.
CONFIGURE_OPTIONS += --disable-introspection

# The build process modifies the shebang line to use the version of Python
# automatically found; to avoid using the current system default, one is
# explicitly specified here.
CONFIGURE_ENV += PYTHON=$(PYTHON)

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES.32)

PYTHON_ARCH_SUBDIR.32 =
PYTHON_ARCH_SUBDIR.64 = /64
PYTHON_ARCH_SUBDIR = $(PYTHON_ARCH_SUBDIR.$(BITS))
COMPONENT_BUILD_ARGS += pyexecsubdir=$(PYTHON_ARCH_SUBDIR)
COMPONENT_INSTALL_ARGS += pyexecsubdir=$(PYTHON_ARCH_SUBDIR)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += runtime/python-27
