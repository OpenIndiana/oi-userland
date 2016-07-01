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
COMPILER =		gcc
BUILD_BITS =		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pygobject
COMPONENT_VERSION=	3.18.2
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/PyGObject
COMPONENT_ARCHIVE_HASH= \
	sha256:2a3cad1517916b74e131e6002c3824361aee0671ffb0d55ded119477fc1c2c5f
COMPONENT_BUGDB=       gnome/libraries

TPNO=			25832

# Needs gobject-introspection >= 1.39.0, which is not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

# Only build for 2.7 for now as we need 32-bit and 64-bit support; all of the
# GNOME and desktop components must be built for Python 2.7 for now.
PYTHON_VERSIONS= 2.7

# Tests do not yet work with Userland framework - 23712631
TEST_TARGET= $(SKIP_TEST)
include $(WS_MAKE_RULES)/gnome-component.mk

# Required due to patch to configure.ac.
COMPONENT_PREP_ACTION += ( cd $(@D) ; NOCONFIGURE=1 $(CONFIG_SHELL) autogen.sh );

# Needs -std=c99 at minimum for 'NAN', etc.
CFLAGS += -std=c11

CONFIGURE_OPTIONS += --disable-static

# The build process modifies the shebang line to use the version of Python
# automatically found; to avoid using the current system default, one is
# explicitly specified here.
CONFIGURE_OPTIONS += --with-python=$(PYTHON)

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/python/pycairo-27
# Pyflakes is needed for tests, but not build or install
REQUIRED_PACKAGES += library/python/pyflakes
REQUIRED_PACKAGES += runtime/python-27
