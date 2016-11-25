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
# Copyright 2016 Gary Mills
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libgphoto2
COMPONENT_VERSION= 2.4.14
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Digital camera library - 2.4 compatibility package
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:59b32d45252f67d066cc3bda7a59f8078e0cf4e7f23590a4b621633e81060292
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/gphoto/files/libgphoto/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gphoto.org

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS.32 += -D_FILE_OFFSET_BITS=64
CFLAGS += $(CFLAGS.$(BITS))

CONFIGURE_OPTIONS+= --with-doc-dir=/usr/share/doc/libgphoto2
CONFIGURE_OPTIONS+= --disable-static

ENV = /usr/bin/env -i

# 64-bit build needs 64-bit libexif
# and we currently don't ship one
build: $(BUILD_32)

install: $(INSTALL_32)

test: $(TEST_32)
