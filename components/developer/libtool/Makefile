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
# Copyright 2017 Aurelien Larcher
# Copyright 2017 Gary Mills
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libtool
COMPONENT_VERSION=      2.4.7
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=      GNU libtool
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/libtool/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:4f7f217f057ce655ff22559ad221a0fd8ef84ad1fc5fcb6990cecc333aa1635d
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/build/libtool
COMPONENT_CLASSIFICATION=Development/GNU
COMPONENT_LICENSE=      GPLv2, FDLv1.3

# For now, we want to continue to provide the libltdl.so's (and their
# links) from libtool 1.5.22.
#
COMPONENT_VERSION_1= 1.5.22
COMPONENT_SRC_1= $(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:88e9ffaaade21c1ddaf6297723dd2fb4ca18ccaef0499a28b6e672f02c8ceb5d
COMPONENT_ARCHIVE_URL_1= https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE_1)
SOURCE_DIR_1= $(COMPONENT_DIR)/$(COMPONENT_SRC_1)

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += PERL="$(PERL)"

COMPONENT_PREP_ACTION= ( cd $(@D) ; $(TOUCH) $(SOURCE_DIR)/README-release ; PATH="$(PATH)" ./bootstrap --force --no-git )

# Remove the hard-wired compiler locations in the LTCC and two CC lines
# in the two versions of the libtool script.
COMPONENT_POST_INSTALL_ACTION= \
	(for dir in $(PROTOUSRBINDIR) $(PROTOUSRBINDIR)/$(MACH64) ; do \
		cd $$dir; \
		/usr/gnu/bin/sed -i \
			-e 's|^LTCC="/.*$$|LTCC="gcc"|' \
			-e 's|^CC="/.*$$|CC="gcc"|' libtool ; \
	done)

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^\#\#/p" ' \
	'-e "/ok/p" ' \
	'-e "/skipped/p" ' \
	'-e "/expected failure/p" ' \
	'-e "/FAILED/p" '

# Macros to configure, build, and install the old version for the time being.
BUILD_OLD_DIR_32= $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64= $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured:	BITS=32
$(BUILD_OLD_DIR_64)/.configured:	BITS=64

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# install the old version first
$(BUILD_DIR_32)/.installed:	$(BUILD_OLD_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:	$(BUILD_OLD_DIR_64)/.installed

# we need to prep the old version too (this should be handled in prep.mk)
$(SOURCE_DIR_1)/.unpacked:        download Makefile $(PATCHES)
	$(RM) -r $(SOURCE_DIR_1)
	$(UNPACK) $(UNPACK_ARGS) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)
	$(TOUCH) $@

# prep the old version first
$(SOURCE_DIR)/.prep:	$(SOURCE_DIR_1)/.prep

$(SOURCE_DIR_1)/.prep:        $(SOURCE_DIR_1)/.unpacked
	$(TOUCH) $@

prep::	$(SOURCE_DIR_1)/.prep

CLEAN_PATHS += $(SOURCE_DIR_1)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/linker
REQUIRED_PACKAGES += developer/object-file
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-sed
