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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= smp_utils
COMPONENT_VERSION= 0.98
COMPONENT_SUMMARY= Utilities for the Serial Attached SCSI (SAS) Serial Management Protocol (SMP)
COMPONENT_PROJECT_URL= http://sg.danny.cz/sg/smp_utils.html
COMPONENT_FMRI= system/storage/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_URL= http://sg.danny.cz/sg/p/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:eb1952a192992bc60c7c84301f43d57fd386d6dcc9eef3f018a94114a38bb7e0
COMPONENT_BUGDB= utility/smp_utils
COMPONENT_LICENSE = FreeBSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --bindir ${CONFIGURE_SBINDIR.32}

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:	 $(TEST_32)

REQUIRED_PACKAGES += system/library
