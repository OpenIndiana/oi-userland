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
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= avahi
COMPONENT_VERSION= 0.8
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Avahi client and bridge to pkg://service/network/dns/mdns
COMPONENT_PROJECT_URL=	https://avahi.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/lathiat/avahi/releases/download/v0.8/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:060309d7a333d38d951bc27598c677af1796934dbd98e1024e7ad8de798fedda
COMPONENT_FMRI=			system/network/avahi
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += ( \
	cd $(@D) && \
	aclocal -I common && \
	automake --add-missing && \
	autoconf )

# Need this to build service-type-database
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CP) -r $(SOURCE_DIR)/* $(@D) )

LDFLAGS += -ldns_sd

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-avahi-user=daemon
CONFIGURE_OPTIONS += --with-avahi-group=other
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-distro=none
CONFIGURE_OPTIONS += --disable-gtk3
CONFIGURE_OPTIONS += --disable-qt3
CONFIGURE_OPTIONS += --disable-qt4
CONFIGURE_OPTIONS += --disable-mono
CONFIGURE_OPTIONS += --disable-monodoc
CONFIGURE_OPTIONS += --enable-tests
CONFIGURE_OPTIONS += --disable-compat-howl
CONFIGURE_OPTIONS += --disable-compat-libdns_sd
CONFIGURE_OPTIONS += --disable-autoipd
CONFIGURE_OPTIONS += --disable-dependency-tracking
# We don't want 32 bit gui
CONFIGURE_OPTIONS.32 += --disable-gtk
CONFIGURE_OPTIONS.32 += --disable-gtk3
CONFIGURE_OPTIONS.32 += --disable-qt5
CONFIGURE_OPTIONS.32 += --disable-pygobject

CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV += MSGFMT=/usr/gnu/bin/msgfmt

CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
# to get link dependencies for QT5 right.
CONFIGURE_ENV += QT5_LIBS="-L/usr/lib/qt/5.15/lib/$(MACH64)"
# to find Qt5Core.pc
PKG_CONFIG_PATH.prepend += $(QT5_PKG_CONFIG_PATH)

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# make gcc-14 happy
CFLAGS += -Wno-implicit-function-declaration -Wno-int-conversion -Wno-incompatible-pointer-types

# Manually added build dependencies
REQUIRED_PACKAGES += text/xmltoman

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += library/libdaemon
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus/32
REQUIRED_PACKAGES.python += library/python/dbus-python
REQUIRED_PACKAGES.python += library/python/pygobject
REQUIRED_PACKAGES.python += runtime/python
