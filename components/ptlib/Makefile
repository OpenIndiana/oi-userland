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

COMPONENT_NAME= ptlib

COMPONENT_VERSION= 2.6.7
COMPONENT_SUMMARY= PTLib Class Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b8add72c24e52cf1d76fcee6dbf6f96b69e5c09a64ecb0d0d06b2c17b4ee26c9
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/ptlib/2.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION=( cd $(@D)/plugins && aclocal && autoconf &&\
		cd $(@D)&& aclocal && autoconf)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_PREFIX=/usr/g++

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-resolver
CONFIGURE_OPTIONS += --enable-opal
CONFIGURE_OPTIONS += --disable-openssl
CONFIGURE_OPTIONS += --enable-sunaudio
CONFIGURE_OPTIONS += --enable-url
CONFIGURE_OPTIONS += --enable-http
CONFIGURE_OPTIONS += --enable-httpforms
CONFIGURE_OPTIONS += --enable-httpsvc
CONFIGURE_OPTIONS += --enable-v4l2

ENV += -i

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
