#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2013 Alexander Pyhalov
#

BUILD_STYLE = archive
BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipcalc
COMPONENT_VERSION=	0.41
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://jodies.de/ipcalc
COMPONENT_SUMMARY=	IP Calculator
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dda9c571ce3369e5b6b06e92790434b54bec1f2b03f1c9df054c0988aa4e2e8a
COMPONENT_ARCHIVE_URL=	http://jodies.de/ipcalc-archive/$(COMPONENT_ARCHIVE)

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

include $(WS_TOP)/make-rules/common.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_$(MK_BITS)): $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)): $(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR)/usr/bin 
	cp $(SOURCE_DIR)/ipcalc $(PROTO_DIR)/usr/bin/ipcalc
	$(TOUCH) $@

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
