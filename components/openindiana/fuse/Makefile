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
# Copyright 2016, Adam Stevko
#

BUILD_STYLE = justmake
BUILD_BITS = 64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-fusefs
COMPONENT_VERSION=	f7c3e8c785091774d75d4f11ac12f2309a3f2dbd
IPS_COMPONENT_VERSION=	1.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:06551185d2709b4ce043d98e97fccb0a375f5c4161550e594449ce09f09e8aab
COMPONENT_ARCHIVE_URL=	https://github.com/jurikm/illumos-fusefs/archive/$(COMPONENT_VERSION).zip

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Force gcc 7 for a case we would switch our default gcc to something else.
# This should match the compiler used to build illumos-gate.
# Now switched to gcc 10
GCC_VERSION = 10

PATH=/opt/onbld/bin/i386:$(PATH.illumos)

$(BUILD_$(MK_BITS)):	$(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	(cd $(@D)/kernel && $(ENV) - CC=$(CC) PATH=$(PATH) dmake -e)
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)):	$(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR)

	(cd $(@D)/kernel && dmake install)

	$(MKDIR) $(PROTOUSRKERNELDRVDIR) $(PROTOUSRKERNELDRVDIR64)

	$(INSTALL) $(@D)/kernel/proto/$(USRKERNELDRVDIR64)/fuse $(PROTOUSRKERNELDRVDIR64)
	$(INSTALL) $(@D)/kernel/proto/$(USRKERNELDRVDIR)/fuse.conf $(PROTOUSRKERNELDRVDIR)

	$(TOUCH) $@

# Auto-generated dependencies
