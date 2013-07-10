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
# Copyright 2013, Adam Stevko. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         arcstat
COMPONENT_VERSION=      0.5
COMPONENT_GIT_REV=      0b4546e
COMPONENT_LICENSE=      CDDL
COMPONENT_SRC=		mharsch-arcstat-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5533b281c61c0c8e500b22893a4e6b97945f97096de77e921e051108e4369860
COMPONENT_PROJECT_URL=  https://github.com/mharsch/arcstat
COMPONENT_ARCHIVE_URL=  https://codeload.github.com/mharsch/arcstat/legacy.tar.gz/$(COMPONENT_GIT_REV)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

install: prep
	$(MKDIR) $(PROTOUSRBINDIR)
	$(CP) $(SOURCE_DIR)/arcstat.pl $(PROTOUSRBINDIR)/arcstat

publish: install

clean::
	$(RM) -r $(BUILD_DIR)
