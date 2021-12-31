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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyatspi
# Notes: updating this package would also need to update at-spi2-core, orca and possibly others, too. pyatspi > 2.35 use gtk3.
COMPONENT_MJR_VERSION=	2.24
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY=	Python API to AT-SPI on D-Bus
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Accessibility
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:e7ef47a5d387fdc64a01722ef2bcced54c4d6b225fbe34867189e1f88ff0a692
COMPONENT_ARCHIVE_URL=	https://ftp.gnome.org/pub/GNOME/sources/pyatspi/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/python/pyatspi2
COMPONENT_CLASSIFICATION=	Applications/Universal Access
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

PATH=$(PATH.gnu)

PYTHON_VERSIONS = 3.5

VARIANT_PYTHON35 = $(BUILD_DIR)/python-35

VARIANTS = $(VARIANT_PYTHON35)

# PGK_CONFIG_PATH is needed to make configure find pygobject-3
PKG_CONFIG_PATH= $(PKG_CONFIG_PATH.64):$(PKG_CONFIG_PATH.32)

BUILD_NO_ARCH = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_NO_ARCH = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANT_PYTHON35)/$(MACH64)/.configured: PYTHON=$(PYTHON.3.5.64)
$(VARIANT_PYTHON35)/$(MACH64)/.configured: am_cv_python_pyexecdir=$(PYTHON.3.5.VENDOR_PACKAGES.64)
$(VARIANT_PYTHON35)/$(MACH64)/.configured: am_cv_python_pythondir=$(PYTHON.3.5.VENDOR_PACKAGES.64)

# Tests don't work as configure doesn't find the python dbus module
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-python=$(PYTHON)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-tests

CONFIGURE_ENV+=		PYTHON=$(PYTHON)
# Ensure Python modules are installed into vendor package directories:
CONFIGURE_ENV+=		am_cv_python_pythondir="$(am_cv_python_pythondir)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(am_cv_python_pyexecdir)"

# Manually added dependencies
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += runtime/python-35

# Auto-generated dependencies
