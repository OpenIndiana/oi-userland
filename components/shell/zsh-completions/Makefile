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
# Copyright 2018 Michal Nowak
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zsh-completions
COMPONENT_VERSION=	0.35.0
COMPONENT_SUMMARY=	Additional completion definitions for Zsh.
COMPONENT_PROJECT_URL=	https://github.com/zsh-users/zsh-completions
COMPONENT_FMRI=		utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/zsh-users/zsh-completions/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:811bb4213622720872e08d6e0857f1dd7bc12ff7aa2099a170b76301a53f4fbe
COMPONENT_LICENSE=	Various
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CLEAN_PATHS += $(BUILD_DIR)

$(BUILD_64):    $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D)
	$(TOUCH) $@

$(INSTALL_64): $(BUILD_64)
	$(MKDIR) $(PROTO_DIR)
	$(MKDIR) $(PROTOUSRSHAREDIR)/$(COMPONENT_NAME)

	$(CP) -a $(SOURCE_DIR)/src/* $(PROTOUSRSHAREDIR)/$(COMPONENT_NAME)

	$(TOUCH) $@

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/zsh
