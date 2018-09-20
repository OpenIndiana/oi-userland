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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyatspi
COMPONENT_MJR_VERSION=	2.24
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Accessibility
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e7ef47a5d387fdc64a01722ef2bcced54c4d6b225fbe34867189e1f88ff0a692
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/pyatspi/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

PATH=$(PATH.gnu)

PYTHON_VERSIONS = 3.4 3.5

VARIANT_PYTHON34 = $(BUILD_DIR)/python-34
VARIANT_PYTHON35 = $(BUILD_DIR)/python-35

VARIANTS = $(VARIANT_PYTHON34) $(VARIANT_PYTHON35)

BUILD_NO_ARCH = $(VARIANTS:%=%/$(MACH32)/.built)

INSTALL_NO_ARCH = $(VARIANTS:%=%/$(MACH32)/.installed)

$(VARIANT_PYTHON34)/$(MACH32)/.configured: PYTHON=$(PYTHON.3.4.32)
$(VARIANT_PYTHON34)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.3.4.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON34)/$(MACH32)/.configured: am_cv_python_pythondir=$(PYTHON.3.4.VENDOR_PACKAGES.32)

$(VARIANT_PYTHON35)/$(MACH32)/.configured: PYTHON=$(PYTHON.3.5.32)
$(VARIANT_PYTHON35)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.3.5.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON35)/$(MACH32)/.configured: am_cv_python_pythondir=$(PYTHON.3.5.VENDOR_PACKAGES.32)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--with-python=$(PYTHON)
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pythondir="$(am_cv_python_pythondir)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(am_cv_python_pyexecdir)"

# common targets
# Doesn't contain binary modules 
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)
