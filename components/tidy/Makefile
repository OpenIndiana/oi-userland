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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tidy
COMPONENT_VERSION=	1.0.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:305704f7569b9e0abea81033f609f9a19dbbcfe2
COMPONENT_ARCHIVE_URL=	http://static.opensolaris.org/tarball/userland/$(COMPONENT_ARCHIVE)


include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

#tree.js, treeview.js, tidyenum_8h.html are installed 
#from files directory manually as doxygen didn't generate them.
#This needs to be fixed later. 

COMPONENT_PREP_ACTION =  \
        (cd $(SOURCE_DIR); doxygen htmldoc/doxygen.cfg)

CONFIGURE_OPTIONS  +=       --disable-static 
CONFIGURE_OPTIONS  +=       --enable-access 
CONFIGURE_OPTIONS  +=       --enable-utf16 
CONFIGURE_OPTIONS  +=       --enable-asian
CONFIGURE_OPTIONS  +=	    CFLAGS="$(CFLAGS)"

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CP) -r $(SOURCE_DIR)/test $(@D))

PROTODOCDIR=$(PROTOUSRSHAREDIR)/doc/tidy

$(PROTODOCDIR):
	$(MKDIR) $@

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(PROTODOCDIR)
		$(CP) -r $(SOURCE_DIR)/htmldoc/api $(PROTODOCDIR)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
