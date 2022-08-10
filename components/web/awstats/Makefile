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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE = archive
BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= awstats
COMPONENT_VERSION= 7.8
COMPONENT_REVISION =	1
COMPONENT_SUMMARY= AWStats - Log File Analyzer for Advanced Statistics
COMPONENT_FMRI= web/analytics/awstats
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4a65867e01bef6a9bdba3e9e411fb2a0e0d87bc4c85ff02e3cbfca001a04d4b8
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/awstats/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://awstats.sourceforge.net/
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_LICENSE=		GPLv3

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_$(MK_BITS)): $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)):  $(BUILD_$(MK_BITS))
	$(RM) -r $(PROTO_DIR)
	$(MKDIR) $(PROTO_DIR)/usr/lib/awstats
	$(CP) -r $(@D)/README.md $(@D)/tools $(PROTO_DIR)/usr/lib/awstats
	$(MKDIR) $(PROTO_DIR)/usr/share/doc/awstats
	$(CP) -r $(@D)/docs $(PROTO_DIR)/usr/share/doc/awstats
	$(MKDIR) $(PROTO_DIR)/usr/share/awstats
	$(CP) -r $(@D)/wwwroot/* $(PROTO_DIR)/usr/share/awstats
	$(TOUCH) $@

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
