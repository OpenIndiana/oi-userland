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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dbus-python
COMPONENT_VERSION=	1.2.4
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/DBusBindings/
COMPONENT_SUMMARY=	Python bindings for D-Bus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e2f1d6871f74fba23652e51d10873e54f71adab0525833c19bad9e99b1b2f9cc
COMPONENT_ARCHIVE_URL=	http://dbus.freedesktop.org/releases/dbus-python/$(COMPONENT_ARCHIVE)

PATH=/usr/gnu/bin:/usr/bin

gcc_OPT		= -O2

VARIANT_PYTHON26 = $(BUILD_DIR)/python-26
VARIANT_PYTHON27 = $(BUILD_DIR)/python-27

VARIANTS = $(VARIANT_PYTHON26) $(VARIANT_PYTHON27)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

# Avoid overwriting python2.7 files in /usr/share
$(VARIANT_PYTHON27)/$(MACH32)/.installed:       $(VARIANT_PYTHON26)/$(MACH32)/.installed
$(VARIANT_PYTHON27)/$(MACH64)/.installed:       $(VARIANT_PYTHON26)/$(MACH64)/.installed

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

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--with-dbus-user=root
CONFIGURE_OPTIONS+=	--with-dbus-daemondir=/usr/lib
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pythondir="$(am_cv_python_pythondir)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(am_cv_python_pyexecdir)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library
