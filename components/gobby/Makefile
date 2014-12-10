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

COMPONENT_NAME= gobby
COMPONENT_VERSION= 0.4.94
COMPONENT_REVISION= 1
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=editor/gobby
COMPONENT_SUMMARY= A collaborative text editor
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b9798808447cd94178430f0fb273d0e45d0ca30ab04560e3790bac469e03bb00
COMPONENT_ARCHIVE_URL= \
  http://releases.0x539.de/gobby/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gobby.0x539.de
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

LDFLAGS += -lnsl -lsocket

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
