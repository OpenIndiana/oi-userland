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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtool
COMPONENT_VERSION=	2.4.2
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/libtool/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:22b71a8b5ce3ad86e1094e7285981cae10e6ff88
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

# For now, we want to continue to provide the libltdl.so's (and their
# links) from libtool 1.5.22.
#
COMPONENT_VERSION_1 =	1.5.22
COMPONENT_SRC_1 =	$(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1 =	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1 = sha1:17353e66aeaac80ae188ea0a3a90609550ce3254
COMPONENT_ARCHIVE_URL_1 = http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE_1)
SOURCE_DIR_1 =		$(COMPONENT_DIR)/$(COMPONENT_SRC_1)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		PERL="$(PERL)"

COMPONENT_PREP_ACTION = (cd $(@D) ; ./bootstrap)

# Remove the hard-wired compiler locations in the LTCC and two CC lines
# in the two versions of the libtool script.
COMPONENT_POST_INSTALL_ACTION = \
	(for dir in $(PROTOUSRBINDIR) $(PROTOUSRBINDIR)/$(MACH64) ; do \
		cd $$dir; \
		/usr/gnu/bin/sed -i \
			-e 's|^LTCC="/.*$$|LTCC="cc"|' \
			-e 's|^CC="/.*$$|CC="cc"|' libtool ; \
	done)

# Macros to configure, build, and install the old version for the time being.
BUILD_OLD_DIR_32 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64 = $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

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
	$(UNPACK) $(UNPACK_ARGS) $(COMPONENT_ARCHIVE_1)
	$(TOUCH) $@

# prep the old version first
$(SOURCE_DIR)/.prep:	$(SOURCE_DIR_1)/.prep

$(SOURCE_DIR_1)/.prep:        $(SOURCE_DIR_1)/.unpacked
	$(TOUCH) $@

prep::	$(SOURCE_DIR_1)/.prep


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
