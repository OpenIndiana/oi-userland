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

COMPONENT_NAME= opal

COMPONENT_VERSION= 3.6.8
COMPONENT_SUMMARY= OPAL - Open Phone Abstraction Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:7d7aa0238e7d5280d9adcdfa7c6bb2a15bf8add66a0b11260f52c7117ff23abd
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKG_CONFIG_PATH.32   = /usr/g++/lib/pkgconfig:/usr/lib/pkgconfig

COMPONENT_PREP_ACTION=( cd $(@D)/plugins && aclocal && autoconf &&\
		cd $(@D)&& aclocal && autoconf)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX=/usr/g++

LDFLAGS.32  +=  -L/usr/g++/lib -R/usr/g++/lib
LDFLAGS += $(LDFLAGS.$(BITS))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-iax

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
