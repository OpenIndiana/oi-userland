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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tidy
COMPONENT_VERSION=	1.0.0
COMPONENT_PROJECT_URL=	http://tidy.sourceforge.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:074023e48ed151db743d194af1028e4a17fa72a18e4069b4f18d4683db4bb9cf
COMPONENT_ARCHIVE_URL=	$(EXTERNAL_ARCHIVE_MIRROR)/$(SOURCE_ARCHIVE)
COMPONENT_BUGDB=	library/tidy

TPNO=			9098

SYSTEM_TEST_TARGET= $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

#tree.js, treeview.js, tidyenum_8h.html are installed 
#from files directory manually as doxygen didn't generate them.
#This needs to be fixed later. 

COMPONENT_PREP_ACTION =  \
        (cd $(SOURCE_DIR); doxygen htmldoc/doxygen.cfg)

CONFIGURE_OPTIONS  +=       --disable-static 
CONFIGURE_OPTIONS  +=       --enable-access 
CONFIGURE_OPTIONS  +=       --enable-utf16 
CONFIGURE_OPTIONS  +=       --enable-asian

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) -r $(SOURCE_DIR)/test $(@D))

PROTODOCDIR=$(PROTOUSRSHAREDOCDIR)/tidy

COMPONENT_TEST_DIR =    $(@D)/test
COMPONENT_TEST_CMD =	./testall.sh
COMPONENT_TEST_TARGETS =

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_SYSTEM_TEST_ENV =	TIDY_BIN=/usr/bin/tidy
COMPONENT_SYSTEM_TEST_DIR =	$(SOURCE_DIR)/test
COMPONENT_SYSTEM_TEST_CMD =	./testall.sh
COMPONENT_SYSTEM_TEST_TARGETS =

COMPONENT_POST_INSTALL_ACTION += \
		($(MKDIR) $(PROTODOCDIR); \
		$(CP) -r $(SOURCE_DIR)/htmldoc/api $(PROTODOCDIR))

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
