#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2013-2020, Aurelien Larcher. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xcb-proto
COMPONENT_VERSION=        1.16.0
COMPONENT_SUMMARY=        The X protocol C-language Binding (XCB): Protocol descriptions
COMPONENT_PROJECT_URL=    https://xcb.freedesktop.org
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	  sha256:a75a1848ad2a89a82d841a51be56ce988ff3c63a8d6bf4383ae3219d8d915119
COMPONENT_ARCHIVE_URL=    https://xorg.freedesktop.org/archive/individual/proto/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           x11/header/xcb-protocols
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_LICENSE=        MIT
COMPONENT_LICENSE_FILE=   COPYING

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS+= PYVER="$(PYTHON_VERSION)"

CONFIGURE_ENV += PYTHON=$(PYTHON)
CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros
REQUIRED_PACKAGES += library/libxml2

# Manually added dependency on python runtime
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
