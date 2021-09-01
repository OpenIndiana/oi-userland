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
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
# Copyright 2021 Jean-Pierre André. All rights reserved.
#

BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ntfs-3g_ntfsprogs
IPS_COMPONENT_VERSION= 2021.8.22
COMPONENT_VERSION= $(IPS_COMPONENT_VERSION)
COMPONENT_SUMMARY= ntfsprogs - Utilities that provide access to NTFS
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= sha256:55b883aa05d94b2ec746ef3966cb41e66bed6db99f22ddd41d1b8b94bb202efb
COMPONENT_ARCHIVE_URL= https://tuxera.com/opensource/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://github.com/tuxera/ntfs-3g/
COMPONENT_FMRI= system/file-system/ntfsprogs
COMPONENT_CLASSIFICATION= System/Administration and Configuration
COMPONENT_LICENSE= GPLv2, LGPLv2
COMPONENT_LICENSE_FILE= ntfsprogs.license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS += -D__LITTLE_ENDIAN=1234
CFLAGS += -D__BYTE_ORDER=1234

CONFIGURE_OPTIONS += --exec-prefix=/usr
CONFIGURE_OPTIONS += --enable-xattr-mappings
CONFIGURE_OPTIONS += --with-fuse=external

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += system/library
