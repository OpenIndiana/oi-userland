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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= java-atk-wrapper
COMPONENT_VERSION= 0.30.9
COMPONENT_SUMMARY= A wrapper of ATK Bridge for Java Swing apps
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:e67df3b9ec26f2a27a7599b5e031a04d8008d9b27bc5d787a2beaae90d0d0dce
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= gnome/accessibility/java-atk-wrapper
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING.LESSER

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CPPFLAGS += -I$(JAVA_HOME)/include
CPPFLAGS += -I$(JAVA_HOME)/include/solaris

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += JAVA_HOME=$(JAVA_HOME)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
