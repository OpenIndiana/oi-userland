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
# Copyright 2022 Marcel Telka
#

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pstree
COMPONENT_VERSION =		2.40
COMPONENT_SUMMARY =		pstree shows the process listing as a tree
COMPONENT_PROJECT_URL =		https://github.com/FredHucht/pstree
COMPONENT_FMRI =		diagnostic/pstree
COMPONENT_CLASSIFICATION =	Applications/System Utilities
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL =		https://github.com/FredHucht/pstree/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:64d613d8f66685b29f13a80e08cddc08616cf3e315a0692cbbf9de0d8aa376b3
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

$(INSTALL_$(MK_BITS)): $(BUILD_$(MK_BITS))
	$(MKDIR) $(PROTO_DIR) $(PROTOUSRBINDIR) $(PROTOUSRSHAREMAN1DIR)
	$(CP) $(BUILD_DIR_$(BITS))/pstree $(PROTOUSRBINDIR)
	$(CP) $(BUILD_DIR_$(BITS))/pstree.1 $(PROTOUSRSHAREMAN1DIR)
	$(TOUCH) $@

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
