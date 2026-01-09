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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = archive

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			unicode-ucd
COMPONENT_VERSION=		17.0.0
COMPONENT_SUMMARY=		Unicode Character Database data files
COMPONENT_PROJECT_URL=		https://www.unicode.org/ucd/
COMPONENT_FMRI=			data/unicode-ucd
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		UCD-$(HUMAN_VERSION).zip
COMPONENT_ARCHIVE_URL=		https://www.unicode.org/Public/$(HUMAN_VERSION)/ucd/UCD.zip
COMPONENT_ARCHIVE_HASH=		sha256:2066d1909b2ea93916ce092da1c0ee4808ea3ef8407c94b4f14f5b7eb263d28e
COMPONENT_LICENSE=		Unicode-3.0

BUILD_TARGET = $(BUILD_DIR)/.built
INSTALL_TARGET = $(BUILD_DIR)/.installed
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file:
	curl -s https://www.unicode.org/license.txt > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

CLEAN_PATHS += $(BUILD_DIR)
CLEAN_PATHS += $(PROTO_DIR)

UNPACK_ARGS= --relocate-to=$(COMPONENT_SRC)/ucd

$(BUILD_DIR)/.built: $(SOURCE_DIR)/.prep
	$(MKDIR) $(BUILD_DIR)
	$(TOUCH) $@

$(BUILD_DIR)/.installed: $(BUILD_DIR)/.built
	$(MKDIR) $(PROTOUSRSHAREDIR)/unicode
	$(CP) -a $(SOURCE_DIR)/ucd $(PROTOUSRSHAREDIR)/unicode
	$(TOUCH) $@

# Auto-generated dependencies
