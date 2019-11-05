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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= awstats
COMPONENT_VERSION= 7.6
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= AWStats - Log File Analyzer for Advanced Statistics
COMPONENT_FMRI= web/analytics/awstats
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4045501319bf99e223bdb492a68a8f08b8e814b0f144a008726d7bd59114167a
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/awstats/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://awstats.sourceforge.net/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

CLEAN_PATHS += $(BUILD_DIR) $(PROTO_DIR)

$(BUILD_32): $(SOURCE_DIR)/.prep
	$(MKDIR) $(BUILD_DIR_32)
	cp -a $(SOURCE_DIR)/* $(BUILD_DIR_32)
	$(TOUCH) $(@)

$(INSTALL_32):  $(BUILD_32)
	$(RM) -r $(PROTO_DIR)
	$(MKDIR) $(PROTO_DIR)/usr/lib/awstats
	mv $(BUILD_DIR_32)/README.md $(BUILD_DIR_32)/tools $(PROTO_DIR)/usr/lib/awstats
	$(MKDIR) $(PROTO_DIR)/usr/share/doc/awstats
	mv $(BUILD_DIR_32)/docs $(PROTO_DIR)/usr/share/doc/awstats 
	$(MKDIR) $(PROTO_DIR)/usr/share/awstats
	mv $(BUILD_DIR_32)/wwwroot/* $(PROTO_DIR)/usr/share/awstats
	$(TOUCH) $(@)


build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += runtime/perl-522
