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
# Copyright 2016 Adam Stevko.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ntfs-3g_ntfsprogs
COMPONENT_VERSION= 2016.2.22AR.1
IPS_COMPONENT_VERSION= 2016.2.22
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= ntfsprogs - Utilities that provide access to NTFS
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:2091475d439bc5889b09892b7ca97419d600436f13bf28885a29f31137ff3efd
COMPONENT_ARCHIVE_URL= \
	http://jp-andre.pagesperso-orange.fr/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.tuxera.com/community/ntfs-3g-download/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS += -D__LITTLE_ENDIAN=1234
CFLAGS += -D__BYTE_ORDER=1234

CONFIGURE_OPTIONS += --exec-prefix=/usr
CONFIGURE_OPTIONS += --enable-xattr-mappings
CONFIGURE_OPTIONS += --with-fuse=external

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
