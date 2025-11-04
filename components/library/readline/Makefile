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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		readline
HUMAN_VERSION=		8.2p13
COMPONENT_VERSION=	$(subst p,.,$(HUMAN_VERSION))
COMPONENT_SUMMARY=	GNU readline provides interactive line-editing and history
COMPONENT_DESCRIPTION= The GNU Readline library provides a set of functions for use by applications that allow users to edit command lines as they are typed in
COMPONENT_PROJECT_URL= https://tiswww.cwru.edu/php/chet/readline/rltop.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(firstword $(subst p, ,$(HUMAN_VERSION)))
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:08835e57b5eb84f07f8fa50c7530e4b13b08265ffef340e4a4cce4ad6fb575fe
COMPONENT_ARCHIVE_URL= https://ftp.gnu.org/gnu/readline/$(COMPONENT_ARCHIVE)
COMPONENT_VERSION_MAJOR=	$(firstword $(subst ., ,$(HUMAN_VERSION)))
COMPONENT_FMRI=		library/readline-$(COMPONENT_VERSION_MAJOR)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE= COPYING

COMPONENT_FMRI.readline-32=	$(COMPONENT_FMRI)/32

include $(WS_MAKE_RULES)/common.mk

# We need this to handle official patches verbatim
PATCH_LEVEL = 0

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-shared-termcap-library

# Build the readline examples as well (see the INSTALL file).
COMPONENT_BUILD_TARGETS= everything

# Install the additional file
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -Dm0444 $(SOURCE_DIR)/examples/Inputrc $(PROTOUSRDIR)/demo/readline/Inputrc ;

# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

COMPONENT_TEST_DIR= $(@D)/examples
COMPONENT_TEST_CMD= $(CAT) $(SOURCE_DIR)/examples/Inputrc | ./rlcat
COMPONENT_TEST_TARGETS=

# Needed to build the test program.
COMPONENT_PRE_TEST_ACTION += \
	(cd $(@D) ; PATH="$(PATH)" $(GMAKE) libreadline.a ) ;

# Build the test program.
COMPONENT_PRE_TEST_ACTION += \
	(cd $(@D)/examples ; PATH="$(PATH)" $(GMAKE) rlcat ) ;

# Get correct libreadline.so.6 from the proto area.
TEST_LIBPATH.32= $(PROTOUSRLIBDIR)
TEST_LIBPATH.64= $(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

test:		install $(TEST_64_and_32)

# Sanity check
ifneq ($(strip $(COMPONENT_VERSION_MAJOR)),$(strip $(READLINE_VERSION)))
$(error READLINE_VERSION does not match the readline version)
endif

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
