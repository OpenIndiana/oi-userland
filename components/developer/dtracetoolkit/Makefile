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
# Copyright 2021 Gary Mills
# Copyright (c) 2014 Alexander Pyhalov
#

BUILD_STYLE = archive
BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		DTraceToolkit
COMPONENT_VERSION=	0.99
COMPONENT_REVISION=	6
COMPONENT_PROJECT_URL=	http://www.brendangregg.com/dtracetoolkit.html
COMPONENT_SUMMARY=	A collection of opensource dtrace scripts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f4f5df564b79103088731813cbc5c1bab0cb4dec98d2700b8583af190c695266
COMPONENT_ARCHIVE_URL=	http://www.brendangregg.com/DTraceToolkit/$(COMPONENT_ARCHIVE)

BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

include $(WS_TOP)/make-rules/common.mk

$(BUILD_$(MK_BITS)): $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)): $(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR)/opt/DTT 
	$(GTAR) cpf - -C $(SOURCE_DIR) --exclude './.*' . | $(GTAR) xpvf - -C $(PROTO_DIR)/opt/DTT
	$(RM) $(PROTO_DIR)/opt/DTT/install
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/dtrace
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += runtime/ruby-26
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
