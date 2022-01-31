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

COMPONENT_NAME= at-spi2-atk
COMPONENT_VERSION= 2.24.1
COMPONENT_SUMMARY= Assistive Technology Service Provider Interface
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:60dc90ac4f74b8ffe96a9363c25208a443b381bacecfefea6de549f20ed6957d
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/$(COMPONENT_NAME)/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= gnome/accessibility/at-spi2-atk
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

CONFIGURE_ENV += PYTHON=$(PYTHON)

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

$(INSTALL_32):	$(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Tests rely on dbus running, which is not true in zones
test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
