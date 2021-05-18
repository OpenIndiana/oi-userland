#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Grüninger GmbH, Andreas Grüninger (grueni)
#

BUILD_BITS= 64

include ../../../make-rules/shared-macros.mk

GCC_VERSION= 10

COMPONENT_NAME= smp_utils
COMPONENT_VERSION= 0.99
COMPONENT_SUMMARY= Utilities for the Serial Attached SCSI (SAS) Serial Management Protocol (SMP)
COMPONENT_PROJECT_URL= http://sg.danny.cz/sg/smp_utils.html
COMPONENT_FMRI= system/storage/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_URL= http://sg.danny.cz/sg/p/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:f0ecd4532a1d9aff962f5028cfcf191da84274c5d3a1200f57cfbeb545a54b3c
COMPONENT_BUGDB= utility/smp_utils
COMPONENT_LICENSE = FreeBSD

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --bindir ${USRBINDIR}
CONFIGURE_OPTIONS += --sbindir ${USRBINDIR}
CONFIGURE_OPTIONS += --enable-static=no

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

# build dependency
REQUIRED_PACKAGES += developer/gcc-10

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
