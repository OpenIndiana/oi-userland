#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= sg3_utils
COMPONENT_VERSION= 1.47
COMPONENT_SUMMARY= Utilities for devices that use SCSI command sets
COMPONENT_PROJECT_URL= https://sg.danny.cz/sg/sg3_utils.html
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= sha256:8673c7faca849b6b34764332d2aa91f72db05bff7382bb836d0688795199c3e1
COMPONENT_ARCHIVE_URL= https://sg.danny.cz/sg/p/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= system/storage/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE= GPLv2+ and BSD 

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include
CFLAGS += -std=c99 $(CPP_XPG6MODE)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"

# Don't use rpath!
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(BUILD_DIR_64) ; \
	$(GSED) -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' libtool ; \
	$(GSED) -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' libtool)

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
