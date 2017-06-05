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
# Copyright 2016 Adam Stevko 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cronbase
COMPONENT_VERSION=	1.0
COMPONENT_SUMMARY=	cronbase holds root crontab and cron directories.	
COMPONENT_PROJECT_URL=	http://www.openindiana.org
COMPONENT_FMRI=		system/cron/base
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_ARCHIVE_URL=$(COMPONENT_PROJECT_URL)
COMPONENT_LICENSE= CDDL
COMPONENT_LICENSE_FILE= lic_CDDL	

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

$(BUILD_32):
	$(MKDIR) $(BUILD_DIR_32)
	$(TOUCH) $@ 

$(INSTALL_32): $(BUILD_32)

	$(MKDIR) $(PROTOUSRBINDIR) $(PROTOETCDIR)	
	
	$(INSTALL) -m644 $(COMPONENT_DIR)/files/crontab $(PROTOETCDIR)/crontab 
	$(INSTALL) -m755 $(COMPONENT_DIR)/files/run-parts $(PROTOUSRBINDIR)/run-parts

	$(MKDIR) $(PROTOETCDIR)/cron.hourly
	$(MKDIR) $(PROTOETCDIR)/cron.daily
	$(MKDIR) $(PROTOETCDIR)/cron.weekly
	$(MKDIR) $(PROTOETCDIR)/cron.monthly

	$(TOUCH) $@

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
