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
# Copyright 2021-2022 Jean-Pierre André. All rights reserved.
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ntfs-3g_ntfsprogs
COMPONENT_VERSION= 2022.10.3
COMPONENT_SUMMARY= ntfsprogs - Utilities that provide access to NTFS
COMPONENT_SRC= ntfs-3g-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:8bd7749ea9d8534c9f0664d48b576e90b96d45ec8803c9427f6ffaa2f0dde299
COMPONENT_ARCHIVE_URL= https://github.com/tuxera/ntfs-3g/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
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

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS += --exec-prefix=/usr
CONFIGURE_OPTIONS += --enable-xattr-mappings
CONFIGURE_OPTIONS += --with-fuse=external
CONFIGURE_OPTIONS += --disable-static

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
