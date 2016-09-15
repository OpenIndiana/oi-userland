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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

# gobject-introspection bindings are only built correctly for gtk when building
# with gcc, this would otherwise build with Studio.
COMPILER =              gcc
BUILD_BITS =            32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pygtk
COMPONENT_VERSION=	2.24.0
COMPONENT_PROJECT_URL=	http://www.pygtk.org/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:cd1c1ea265bd63ff669e92a2d3c2a88eb26bcd9e5363e0f82c896e649f206912
COMPONENT_BUGDB=       gnome/libraries

TPNO=			19936

# Only build for 2.7 as pygobject-3 will replace pygtk for python 3.x
PYTHON_VERSIONS= 2.7

# Tests do not yet work with Userland framework - 23712629
TEST_TARGET= $(SKIP_TEST)

# Needs newer version of gtk2, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# Required due to patch to configure.ac.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv -I m4);

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += PYTHON=$(PYTHON)

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES.32)

PYTHON_ARCH_SUBDIR.32 =
PYTHON_ARCH_SUBDIR.64 = /64
PYTHON_ARCH_SUBDIR = $(PYTHON_ARCH_SUBDIR.$(BITS))
COMPONENT_BUILD_ARGS += pyexecsubdir=$(PYTHON_ARCH_SUBDIR)
COMPONENT_INSTALL_ARGS += pyexecsubdir=$(PYTHON_ARCH_SUBDIR)

REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/python/python-extra-27
REQUIRED_PACKAGES += runtime/python-27


