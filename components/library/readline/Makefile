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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		readline
COMPONENT_VERSION=	6.3
COMPONENT_REVISION=	4
COMPONENT_SUMMARY=	GNU readline provides interactive line-editing and history
COMPONENT_DESCRIPTION= The GNU Readline library provides a set of functions for use by applications that allow users to edit command lines as they are typed in
COMPONENT_PROJECT_URL=	https://cnswww.cns.cwru.edu/php/chet/readline/rltop.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:56ba6071b9462f980c5a72ab0023893b65ba6debb4eeb475d7a563dc65cafd43
COMPONENT_ARCHIVE_URL= https://ftp.gnu.org/gnu/readline/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/readline
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPLv2, GPLv3, FDLv1.3

# For now, we want to continue to provide the libreadline and libhistory so's
# (and their links) from readline 5.2.
#
COMPONENT_VERSION_1=   5.2
COMPONENT_SRC_1=       $(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=   $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:12e88d96aee2cd1192500356f0535540db499282ca7f76339fb4228c31249f45
COMPONENT_ARCHIVE_URL_1= https://ftp.gnu.org/gnu/readline/$(COMPONENT_ARCHIVE_1)
SOURCE_DIR_1=          $(COMPONENT_DIR)/$(COMPONENT_SRC_1)

include $(WS_MAKE_RULES)/common.mk

CC += $(CC_BITS)

# readline likes to use ld directly and this is the easiest
# way to get it to add -lc
LDFLAGS += -lc
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-static=no

# Build the readline examples as well.
COMPONENT_BUILD_TARGETS= everything

COMPONENT_TEST_DIR= $(@D)/examples
COMPONENT_TEST_CMD= $(CAT) $(SOURCE_DIR)/examples/Inputrc | ./rlcat
COMPONENT_TEST_TARGETS=

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Needed to build the test program.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	(cd $(@D) ; $(GMAKE) libreadline.a ) ;

# Build the test program.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	(cd $(@D)/examples ; $(GMAKE) rlcat ) ;

# Get correct libreadline.so.6 from the proto area.
TEST_LIBPATH.32= $(PROTOUSRLIBDIR)
TEST_LIBPATH.64= $(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

COMPONENT_SYSTEM_TEST_DIR= $(@D)/examples
COMPONENT_SYSTEM_TEST_CMD= $(CAT) $(SOURCE_DIR)/examples/Inputrc | ./rlcat
COMPONENT_SYSTEM_TEST_TARGETS=

# Macros to configure, build, and install the old version for the time being.
BUILD_OLD_DIR_32= $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH32)
BUILD_OLD_DIR_64= $(COMPONENT_DIR)/build/$(COMPONENT_VERSION_1)-$(MACH64)

$(BUILD_OLD_DIR_32)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_64)/.configured: CONFIGURE_SCRIPT = $(SOURCE_DIR_1)/configure
$(BUILD_OLD_DIR_32)/.configured:        BITS=32
$(BUILD_OLD_DIR_64)/.configured:        BITS=64

BUILD_32 += $(BUILD_OLD_DIR_32)/.built
BUILD_64 += $(BUILD_OLD_DIR_64)/.built

INSTALL_32 += $(BUILD_OLD_DIR_32)/.installed
INSTALL_64 += $(BUILD_OLD_DIR_64)/.installed

# install the old version first
$(BUILD_DIR_32)/.installed:     $(BUILD_OLD_DIR_32)/.installed
$(BUILD_DIR_64)/.installed:     $(BUILD_OLD_DIR_64)/.installed

ASLR_MODE= $(ASLR_NOT_APPLICABLE)

test:		install $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
