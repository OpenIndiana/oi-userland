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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= yelp-webkit
COMPONENT_VERSION= 2.30.2
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= The GNOME Help Browser
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:8c49dffecdc07dfe1e1b03f6ec3c32c523650802b6aebaf0b232aaa1af5e9f88
COMPONENT_ARCHIVE_URL= \
  http://distcache.freebsd.org/ports-distfiles/gnome2/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS+= -std=gnu++0x
LDFLAGS+= -lgthread-2.0

CONFIGURE_LOCALSTATEDIR=/var/lib
CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt

build: $(BUILD_32)

install: $(INSTALL_32)
