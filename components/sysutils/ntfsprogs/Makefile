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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ntfs-3g_ntfsprogs
COMPONENT_VERSION= 2016.2.22
COMPONENT_SUMMARY= ntfsprogs - Utilities that provide access to NTFS
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:d7b72c05e4b3493e6095be789a760c9f5f2b141812d5b885f3190c98802f1ea0
COMPONENT_ARCHIVE_URL= \
  http://tuxera.com/opensource/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.tuxera.com/community/ntfs-3g-download/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS += -D__LITTLE_ENDIAN=1234
CFLAGS += -D__BYTE_ORDER=1234

CONFIGURE_OPTIONS += --exec-prefix=/usr
CONFIGURE_OPTIONS += --enable-posix-acls
CONFIGURE_OPTIONS += --enable-xattr-mappings
CONFIGURE_OPTIONS += --disable-ntfs-3g

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
