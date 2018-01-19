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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		DTraceToolkit
COMPONENT_VERSION=	0.99
COMPONENT_REVISION=	4	
COMPONENT_PROJECT_URL=	http://www.brendangregg.com/dtracetoolkit.html
COMPONENT_SUMMARY=	A collection of opensource dtrace scripts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f4f5df564b79103088731813cbc5c1bab0cb4dec98d2700b8583af190c695266
COMPONENT_ARCHIVE_URL=	http://www.brendangregg.com/DTraceToolkit/$(COMPONENT_ARCHIVE)

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
	$(MKDIR) $(PROTO_DIR)/opt/DTT 
	/usr/gnu/bin/tar cpf - -C $(SOURCE_DIR) --exclude './.*' . | /usr/gnu/bin/tar xpvf - -C $(PROTO_DIR)/opt/DTT
	rm $(PROTO_DIR)/opt/DTT/install
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/dtrace
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/ruby-23
