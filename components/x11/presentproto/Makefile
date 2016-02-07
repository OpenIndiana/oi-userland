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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           presentproto
COMPONENT_VERSION=        1.0
COMPONENT_FMRI=           x11/header/presentproto
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  headers for the Present extension to the X11 protocol
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:812c7d48721f909a0f7a2cb1e91f6eead76159a36c4712f4579ca587552839ce
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/proto/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var

COMPONENT_INSTALL_ARGS += pkgconfigdir=/usr/share/pkgconfig

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

