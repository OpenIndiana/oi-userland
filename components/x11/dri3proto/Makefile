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

COMPONENT_NAME=           dri3proto
COMPONENT_VERSION=        1.0
COMPONENT_FMRI=           x11/header/dri3proto
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  headers for DRI3 extension to the X11 protocol
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:01be49d70200518b9a6b297131f6cc71f4ea2de17436896af153226a774fc074
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/proto/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+= --without-xmlto
CONFIGURE_OPTIONS+= --with-asciidoc
CONFIGURE_OPTIONS+= --without-fop

COMPONENT_INSTALL_ARGS += pkgconfigdir=/usr/share/pkgconfig

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

