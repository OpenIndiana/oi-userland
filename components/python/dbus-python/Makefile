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
# Copyright 2019 Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dbus-python
COMPONENT_VERSION=	1.2.16
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/DBusBindings/
COMPONENT_SUMMARY=	Python bindings for D-Bus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:11238f1d86c995d8aed2e22f04a1e3779f0d70e587caffeab4857f3c662ed5a4
COMPONENT_ARCHIVE_URL=	http://dbus.freedesktop.org/releases/dbus-python/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/python/python-dbus
COMPONENT_CLASSIFICATTION= Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

PATH=$(PATH.gnu)

PYTHON_VERSION = 3.5
PYTHON_VERSIONS = 3.5

include $(WS_MAKE_RULES)/common.mk

#COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_ENV+=		PYTHON=$(PYTHON)
CONFIGURE_ENV+=		am_cv_python_pythondir="$(PYTHON.3.5.VENDOR_PACKAGES)"
CONFIGURE_ENV+=		am_cv_python_pyexecdir="$(PYTHON.3.5.VENDOR_PACKAGES)"

REQUIRED_PACKAGES += runtime/python-35

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
