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

COMPONENT_NAME= libinfinity
COMPONENT_VERSION= 0.5.5
COMPONENT_SUMMARY= libinfinity is library to build collaborative text editors
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:47c6ee9724bfc9e0d8d89e04d22aca0000b9449c3c39efffa9a66cb717b78cc4
COMPONENT_ARCHIVE_URL= \
  http://releases.0x539.de/libinfinity/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gobby.0x539.de/trac/wiki/Infinote/Libinfinity
COMPONENT_FMRI=library/libinfinity
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Neccessary for tests
ENV =	/usr/bin/env -i

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
