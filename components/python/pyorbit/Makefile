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
# Copyright 2017 Gary Mills
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyorbit
COMPONENT_VERSION=	2.24.0
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8754669b8220aa1f151b920360029d5ea28c42bec55769059676725fe28397b8
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/pyorbit/2.24/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

VARIANT_PYTHON27 = $(BUILD_DIR)/python-27

VARIANTS = $(VARIANT_PYTHON27)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANT_PYTHON27)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.7.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pythondir=$(PYTHON.2.7.VENDOR_PACKAGES.32)

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pyexecdir=$(am_cv_python_pyexecdir)
CONFIGURE_ENV+=		am_cv_python_pythondir=$(am_cv_python_pythondir)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/orbit2
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
