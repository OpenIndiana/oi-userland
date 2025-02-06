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
# Copyright 2024 Andreas Wacknitz
#

BUILD_STYLE= archive
BUILD_BITS= NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		easy-rsa
COMPONENT_FILENAME=	EasyRSA
COMPONENT_VERSION=	3.2.1
COMPONENT_SUMMARY=	Simple shell based CA utility
COMPONENT_SRC=		$(COMPONENT_FILENAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ec0fdca46c07afef341e0e0eeb2bf0cfe74a11322b77163e5d764d28cb4eec89
COMPONENT_PROJECT_URL=	https://github.com/OpenVPN/easy-rsa
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/v$(COMPONENT_VERSION)/EasyRSA-$(COMPONENT_VERSION).tgz
COMPONENT_FMRI=		network/openvpn/easy-rsa
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2, ISC
COMPONENT_LICENSE_FILE=	easy-rsa.license

USRSHAREEASYRSA=/usr/share/easy-rsa
BUILD_TARGET = $(BUILD_$(MK_BITS))
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

include $(WS_MAKE_RULES)/common.mk

# Dynamically create the license file from its sources:
easy-rsa.license: $(SOURCE_DIR)/gpl-2.0.txt $(SOURCE_DIR)/mktemp.txt
	cat $? > $@

$(BUILD_$(MK_BITS)): $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_$(MK_BITS)): $(BUILD_$(MK_BITS)) $(COMPONENT_LICENSE_FILE)
	$(MKDIR) $(PROTO_DIR)/$(USRSHAREEASYRSA)
	$(GTAR) cpf - -C $(SOURCE_DIR) --exclude './.*' . | $(GTAR) xpvf - -C $(PROTO_DIR)/$(USRSHAREEASYRSA)
	$(MKDIR) $(PROTOUSRSHAREDIR)/doc/easy-rsa
	$(MV) $(PROTO_DIR)/$(USRSHAREEASYRSA)/doc/* $(PROTOUSRSHAREDIR)/doc/easy-rsa/
	rmdir $(PROTO_DIR)/$(USRSHAREEASYRSA)/doc/
	$(TOUCH) $@

# the license file is dynamically build, thus we also need to remove it
clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR); \
	$(RM) $(COMPONENT_LICENSE_FILE);

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
