#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2021 Andreas Wacknitz
#

# We have a problem because $BITS is not set if BUILD_BITS= 32_and_64 or 64_and_32 and thus QT5_LIBDIR will be empty!
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= avahi
COMPONENT_VERSION= 0.8
COMPONENT_SUMMARY= Avahi client and bridge to pkg://service/network/dns/mdns
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:060309d7a333d38d951bc27598c677af1796934dbd98e1024e7ad8de798fedda
COMPONENT_ARCHIVE_URL=	https://avahi.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://avahi.org
COMPONENT_CLASSIFICATION= Applications/Internet

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += ( \
	cd $(@D) && \
	aclocal -I common && \
	automake --add-missing && \
	autoconf )

# Need this to build service-type-database
COMPONENT_PRE_CONFIGURE_ACTION = ( cp -r $(SOURCE_DIR)/* $(@D) )

# Use Qt5
PATH = $(PATH.gnu):$(QT5_BINDIR)

#LD_OPTIONS += -L$(QT5_LIBDIR) -R$(QT5_LIBDIR)

LDFLAGS += -ldns_sd

CONFIGURE_OPTIONS += PKG_CONFIG_PATH=$(QT5_PKG_CONFIG_PATH)
CONFIGURE_OPTIONS += --with-avahi-user=daemon
CONFIGURE_OPTIONS += --with-avahi-group=other
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-distro=none
CONFIGURE_OPTIONS += --disable-gtk3
#CONFIGURE_OPTIONS += --disable-qt5
CONFIGURE_OPTIONS += --disable-mono
CONFIGURE_OPTIONS += --disable-monodoc
CONFIGURE_OPTIONS += --enable-tests
CONFIGURE_OPTIONS += --disable-compat-howl
CONFIGURE_OPTIONS += --disable-compat-libdns_sd
CONFIGURE_OPTIONS += --disable-autoipd
CONFIGURE_OPTIONS += --disable-gdbm
CONFIGURE_OPTIONS += --enable-dbm
CONFIGURE_OPTIONS.32+= --disable-pygobject

CONFIGURE_ENV	+= XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV	+= MSGFMT=/usr/gnu/bin/msgfmt

CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# Build dependencies
REQUIRED_PACKAGES += text/xmltoman

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libdaemon
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += library/python/python-dbus-35
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/libdbus
# Bogus dependency due to libssp
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
