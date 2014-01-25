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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipcalc
COMPONENT_VERSION=	0.41
COMPONENT_PROJECT_URL=	http://jodies.de/ipcalc
COMPONENT_SUMMARY=	IP Calculator
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dda9c571ce3369e5b6b06e92790434b54bec1f2b03f1c9df054c0988aa4e2e8a
COMPONENT_ARCHIVE_URL=	http://jodies.de/ipcalc-archive/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)

$(BUILD_DIR)/%/.installed: $(BUILD_32)
	$(MKDIR) $(PROTO_DIR)/usr/bin 
	cp $(SOURCE_DIR)/ipcalc $(PROTO_DIR)/usr/bin/ipcalc
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
