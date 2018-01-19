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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gcalctool
# Updating it further requires dconf support
COMPONENT_VERSION= 5.30.2
COMPONENT_SUMMARY= GNOME calculator utility
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:ae095f5b3fbb2a3683a4ea4d98aecd1c22e987ef9d41fd6998934a46952e383b
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/$(COMPONENT_NAME)/5.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Gcalctool
COMPONENT_FMRI= desktop/calculator/gcalctool
COMPONENT_CLASSIFICATION= Applications/Accessories 
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var/lib

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
