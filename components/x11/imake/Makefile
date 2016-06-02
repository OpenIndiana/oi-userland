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

COMPONENT_NAME=           imake
COMPONENT_VERSION=        1.0.7
COMPONENT_FMRI=           developer/build/imake
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  imake - makefile generation tool
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:690c2c4ac1fad2470a5ea73156cf930b8040dc821a0da4e322014a42c045f37e
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/util/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= imake.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+= --enable-mkdirhier
CONFIGURE_OPTIONS+= --disable-ccmakedep
CONFIGURE_OPTIONS+= --disable-cleanlinks
CONFIGURE_OPTIONS+= --disable-makeg
CONFIGURE_OPTIONS+= --disable-mergelib
CONFIGURE_OPTIONS+= --disable-mkhtmlindex
CONFIGURE_OPTIONS+= --disable-revpath
CONFIGURE_OPTIONS+= RAWCPP=/usr/lib/cpp

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

