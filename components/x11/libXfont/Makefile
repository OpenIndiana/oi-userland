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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libXfont
COMPONENT_VERSION= 1.4.9
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= libXfont - library for X servers and utilities to access font files
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:6c6b061a3aa44f0ac95785f9579f6427080c60ae6948b49bcc8d44f63942ad89
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/lib/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_FMRI= x11/library/libxfont
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -f -i)

LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile-vers

CONFIGURE_LIBDIR.32 = /usr/lib/xorg
CONFIGURE_LIBDIR.64 = /usr/lib/xorg/$(MACH64)

CONFIGURE_OPTIONS += --enable-freetype
CONFIGURE_OPTIONS += --enable-fc
CONFIGURE_OPTIONS += --enable-builtins
CONFIGURE_OPTIONS += --with-bzip2

CONFIGURE_ENV += LIB_MAN_SUFFIX=3xfont

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
