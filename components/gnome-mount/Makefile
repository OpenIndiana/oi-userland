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

COMPONENT_NAME= gnome-mount
COMPONENT_VERSION= 0.4
COMPONENT_SUMMARY= Programs for mounting, unmounting and ejecting storage devices
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:fa9456c0cd1adeda962721fed955914bdc23723a403bebf31bd95a1f54211dd8
COMPONENT_ARCHIVE_URL= \
  http://hal.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://hal.freedesktop.org/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --enable-multiuser=no

build: $(BUILD_32)

install: $(INSTALL_32)
