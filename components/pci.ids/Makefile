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
# Copyright 2013 Adam Stevko. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pci.ids
FORMAT=			2.2
SNAPDATE=		$(shell gawk '$$2 == "Version:" { ver = $$3; gsub(/\./, "", ver); print ver }' $(SOURCE_DIR)/$(COMPONENT_NAME))
COMPONENT_SRC=		$(COMPONENT_NAME)-src
COMPONENT_VERSION=	$(FORMAT).$(SNAPDATE)
COMPONENT_FMRI=		system/pciutils/pci.ids
COMPONENT_SUMMARY=	Repository of all known IDs used in PCI devices
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	pci.ids.license
COMPONENT_ARCHIVE_URL=	http://pciids.sourceforge.net/v$(FORMAT)/$(COMPONENT_NAME)
COMPONENT_PROJECT_URL=	http://pciids.sourceforge.net/

include $(WS_TOP)/make-rules/ips.mk

CURL=/usr/bin/curl
GZIP=/usr/bin/gzip 

download:

prep:
	$(MKDIR) $(SOURCE_DIR)
	cd $(SOURCE_DIR); \
	$(CURL) -sO $(COMPONENT_ARCHIVE_URL)

	$(MKDIR) $(BUILD_DIR_32)
	$(TOUCH) $(BUILD_DIR_32)/.prep

install: prep
	$(MKDIR) $(PROTOUSRSHAREDIR)
	$(GZIP) -c $(SOURCE_DIR)/$(COMPONENT_NAME) > $(PROTOUSRSHAREDIR)/$(COMPONENT_NAME).gz
	$(TOUCH) $(BUILD_DIR_32)/.installed

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(SOURCE_DIR) 
