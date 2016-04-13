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
# Copyright 2013-2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pygobject
COMPONENT_VERSION=	2.28.6
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Python bindings for GObject
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:d464699db159f72e41a8d629ab44b7fef6cf8d746e51f576b6fbc4ce317239d3
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.28/$(COMPONENT_ARCHIVE)

VARIANT_PYTHON26 = $(BUILD_DIR)/python-26
VARIANT_PYTHON27 = $(BUILD_DIR)/python-27

VARIANTS = $(VARIANT_PYTHON26) $(VARIANT_PYTHON27)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

# Avoid overwriting python2.6 files in /usr/share
$(VARIANT_PYTHON26)/$(MACH32)/.installed:	$(VARIANT_PYTHON27)/$(MACH32)/.installed
$(VARIANT_PYTHON26)/$(MACH64)/.installed:	$(VARIANT_PYTHON27)/$(MACH64)/.installed

$(VARIANT_PYTHON26)/$(MACH64)/.configured: BITS=64
$(VARIANT_PYTHON27)/$(MACH64)/.configured: BITS=64
$(VARIANT_PYTHON26)/$(MACH64)/.configured: PYTHON=$(PYTHON.2.6.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: PYTHON=$(PYTHON.2.7.64)
$(VARIANT_PYTHON26)/$(MACH64)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.6.VENDOR_PACKAGES.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.64)
$(VARIANT_PYTHON26)/$(MACH64)/.configured: am_cv_python_pythondir=$(PYTHON.2.6.VENDOR_PACKAGES.64)
$(VARIANT_PYTHON27)/$(MACH64)/.configured: am_cv_python_pythondir=$(PYTHON.2.7.VENDOR_PACKAGES.64)

$(VARIANT_PYTHON26)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.6.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: PYTHON=$(PYTHON.2.7.32)
$(VARIANT_PYTHON26)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.6.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pyexecdir=$(PYTHON.2.7.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON26)/$(MACH32)/.configured: am_cv_python_pythondir=$(PYTHON.2.6.VENDOR_PACKAGES.32)
$(VARIANT_PYTHON27)/$(MACH32)/.configured: am_cv_python_pythondir=$(PYTHON.2.7.VENDOR_PACKAGES.32)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION= (cd $(@D) && autoreconf -f -i)

CFLAGS += $(gcc_C99_ENABLE)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--without-ffi
CONFIGURE_ENV+=		PYTHON=$(PYTHON)

CONFIGURE_ENV+=         PYTHON=$(PYTHON)
CONFIGURE_ENV+=         am_cv_python_pythondir="$(am_cv_python_pythondir)"
CONFIGURE_ENV+=         am_cv_python_pyexecdir="$(am_cv_python_pyexecdir)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
