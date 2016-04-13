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

COMPONENT_NAME= xineramaproto
COMPONENT_VERSION= 1.2.1
COMPONENT_SUMMARY= headers & documentation for XINERAMA extension to the X11 protocol
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:977574bb3dc192ecd9c55f59f991ec1dff340be3e31392c95deff423da52485b
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/proto/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.freedesktop.org/wiki/
COMPONENT_FMRI= x11/header/xineramaproto
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= Development/X11

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --without-xmlto
CONFIGURE_OPTIONS+= --with-asciidoc
CONFIGURE_OPTIONS+= --without-fop
CONFIGURE_OPTIONS+= --localstatedir=/var

COMPONENT_INSTALL_ARGS += pkgconfigdir=/usr/share/pkgconfig

build: $(BUILD_32)

install: $(INSTALL_32)
