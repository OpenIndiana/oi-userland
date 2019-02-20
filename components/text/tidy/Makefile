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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tidy
COMPONENT_VERSION=	1.0.0
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://tidy.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:074023e48ed151db743d194af1028e4a17fa72a18e4069b4f18d4683db4bb9cf
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/oi-build/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/tidy

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

PROTODOCDIR=$(PROTOUSRSHAREDIR)/doc/tidy

$(PROTODOCDIR):
	$(MKDIR) $@

# ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_TEST_DIR =    $(@D)/test
COMPONENT_TEST_CMD =    ./testall.sh
COMPONENT_TEST_TARGETS =

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(PROTODOCDIR)
		$(CP) -r $(SOURCE_DIR)/htmldoc/api $(PROTODOCDIR)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
