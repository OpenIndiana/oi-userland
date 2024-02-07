#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS=NO_ARCH
SINGLE_PYTHON_VERSION = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyatspi
# Notes: updating this package would also need to update at-spi2-core, orca and possibly others, too. pyatspi > 2.35 use gtk3.
COMPONENT_MJR_VERSION=	2.24
COMPONENT_MNR_VERSION=	0
COMPONENT_REVISION=	1
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY=	Python API to AT-SPI on D-Bus
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Accessibility
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:e7ef47a5d387fdc64a01722ef2bcced54c4d6b225fbe34867189e1f88ff0a692
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/pyatspi/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/python/pyatspi2
COMPONENT_CLASSIFICATION=	Applications/Universal Access
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

# Tests don't work as configure doesn't find the python dbus module
TEST_TARGET=	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --with-python=$(PYTHON)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-tests

# Ensure Python modules are installed into vendor package directories:
CONFIGURE_ENV+=		am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
