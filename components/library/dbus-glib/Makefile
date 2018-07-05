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
# Copyright 2015 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dbus-glib
COMPONENT_VERSION=	0.110
COMPONENT_PROJECT_URL=	http://dbus.freedesktop.org/doc/dbus-glib/
COMPONENT_SUMMARY=	D-Bus GLib bindings
COMPONENT_FMRI=		system/library/libdbus-glib
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7ce4760cf66c69148f6bd6c92feaabb8812dee30846b24cd0f7395c436d7e825
COMPONENT_ARCHIVE_URL=	http://dbus.freedesktop.org/releases/dbus-glib/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2,AFLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--localstatedir=/var
CONFIGURE_OPTIONS+=	--disable-static

# For tests to pass
unexport SHELLOPTS

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
