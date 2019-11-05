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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ntfs-3g_ntfsprogs
IPS_COMPONENT_VERSION= 2017.3.23
COMPONENT_VERSION= $(IPS_COMPONENT_VERSION)AR.1
COMPONENT_SUMMARY= ntfsprogs - Utilities that provide access to NTFS
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= sha256:fe8cf2b0326000013f25dc2870305f9ae06b3c7df43ce460d450fa87764cde38
COMPONENT_ARCHIVE_URL= http://jp-andre.pagesperso-orange.fr/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.tuxera.com/community/ntfs-3g-download/
COMPONENT_FMRI= system/file-system/ntfsprogs
COMPONENT_CLASSIFICATION= System/Administration and Configuration
COMPONENT_LICENSE= GPLv2, LGPLv2
COMPONENT_LICENSE_FILE= ntfsprogs.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CFLAGS += -D__LITTLE_ENDIAN=1234
CFLAGS += -D__BYTE_ORDER=1234

CONFIGURE_OPTIONS += --exec-prefix=/usr
CONFIGURE_OPTIONS += --enable-xattr-mappings
CONFIGURE_OPTIONS += --with-fuse=external

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build:   $(BUILD_32)

install: $(INSTALL_32)

test:    $(NO_TESTS)

REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += system/library
