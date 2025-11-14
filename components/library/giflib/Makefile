#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2013, Aurelien Larcher. All rights reserved.
# Copyright (c) 2016 Jim Klimov
# Copyright (c) 2025 Klaus Ziegler
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         giflib
COMPONENT_VERSION=      5.2.2
COMPONENT_SUMMARY=      GIFLIB - A library and utilities for processing GIFs
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://giflib.sourceforge.net/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:be7ffbd057cadebe2aa144542fd90c6838c6a083b5e8a9048b8ee3b66b29d5fb
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/giflib/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=         library/giflib
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_POST_CONFIGURE_ACTION += ( \
	cd $(COMPONENT_SRC); \
	$(GSED) -i -e 's/MACH64/$(MACH64)/' -e 's/gcc_OPT/$(gcc_OPT)/' Makefile );

COMPONENT_POST_INSTALL_ACTION += ( \
	$(MV) $(PROTOUSRSHAREMAN3DIR)/giflib.7 $(PROTOUSRSHAREMAN3DIR)/giflib.3; \
	$(GSED) -i -e 's@"7"@"3"@g' $(PROTOUSRSHAREMAN3DIR)/giflib.3 );

OMPONENT_TEST_TRANSFORMS= "-n"
COMPONENT_TEST_TRANSFORMS += "-e '/Testing/p'"
COMPONENT_TEST_TRANSFORMS += "-e '/Checking/p'"
COMPONENT_TEST_TRANSFORMS += "-e '/basic sanity check/p'"
COMPONENT_TEST_TRANSFORMS += "-e '/No output is good news/p'"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
