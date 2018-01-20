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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= avahi
COMPONENT_VERSION= 0.6.31
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Avahi client and bridge to pkg://service/network/dns/mdns
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8372719b24e2dd75de6f59bb1315e600db4fd092805bd1201ed0cb651a2dab48
COMPONENT_ARCHIVE_URL= \
  http://avahi.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://avahi.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION += (cd $(@D) &&\
	        aclocal -I common &&\
		automake --add-missing &&\
		autoconf)

LDFLAGS += -ldns_sd

CONFIGURE_OPTIONS+= --with-avahi-user=daemon
CONFIGURE_OPTIONS+= --with-avahi-group=other
CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var
CONFIGURE_OPTIONS+= --with-distro=none
CONFIGURE_OPTIONS+= --disable-gtk3
CONFIGURE_OPTIONS+= --disable-qt3
CONFIGURE_OPTIONS+= --disable-qt4
CONFIGURE_OPTIONS+= --disable-mono
CONFIGURE_OPTIONS+= --disable-monodoc
CONFIGURE_OPTIONS+= --enable-tests
CONFIGURE_OPTIONS+= --disable-compat-howl
CONFIGURE_OPTIONS+= --disable-compat-libdns_sd
CONFIGURE_OPTIONS+= --disable-autoipd
CONFIGURE_OPTIONS+= --disable-gdbm
CONFIGURE_OPTIONS+= --enable-dbm

CONFIGURE_ENV	+= XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV	+= MSGFMT=/usr/gnu/bin/msgfmt

CONFIGURE_ENV += am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += am_cv_python_pyexecdir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libdaemon
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += library/python/python-twisted-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/libdbus
