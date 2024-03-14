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

BUILD_STYLE= archive
BUILD_BITS= NO_ARCH
SINGLE_PERL_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipcalc
COMPONENT_VERSION=	0.51
COMPONENT_PROJECT_URL=	https://jodies.de/ipcalc
COMPONENT_SUMMARY=	IP Calculator
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a4dbfaeb7511b81830793ab9936bae9d7b1b561ad33e29106faaaf97ba1c117e
COMPONENT_ARCHIVE_URL=	https://github.com/kjokjo/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE= 	GPLv2
COMPONENT_LICENSE_FILE=	license

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

include $(WS_MAKE_RULES)/common.mk

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
