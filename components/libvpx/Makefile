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

COMPONENT_NAME= libvpx
COMPONENT_VERSION= 1.4.0
COMPONENT_SUMMARY= The VP8 Codec SDK
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:eca30ea7fae954286c9fe9de9d377128f36b56ea6b8691427783b20c67bcfc13
COMPONENT_ARCHIVE_URL= \
  https://github.com/webmproject/libvpx/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = http://www.webmproject.org/
COMPONENT_LICENSE = BSD
COMPONENT_LICENSE_FILE = LICENSE
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = library/video/libvpx

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

TARGET.32 = x86-solaris-gcc
TARGET.64 = x86_64-solaris-gcc

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-vp8
CONFIGURE_OPTIONS += --enable-vp9
CONFIGURE_OPTIONS += --enable-postproc
CONFIGURE_OPTIONS += --enable-runtime-cpu-detect
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --disable-unit-tests
CONFIGURE_OPTIONS += --target=$(TARGET.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
