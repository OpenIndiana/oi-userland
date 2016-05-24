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
# Copyright 2015 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= at-spi2-core
COMPONENT_VERSION= 2.18.3
COMPONENT_SUMMARY= Assistive Technology Service Provider Interface
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:ada26add94155f97d0f601a20cb7a0e3fd3ba1588c3520b7288316494027d629
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.18/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= gnome/accessibility/at-spi2-core
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --with-dbus_daemondir=/usr/lib
CONFIGURE_OPTIONS += --enable-xevie=no

CONFIGURE_ENV += PYTHON=$(PYTHON)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

$(INSTALL_32):	$(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Tests rely on dbus running, which is not true in zones
test: $(NO_TESTS)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += text/intltool
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxtst
