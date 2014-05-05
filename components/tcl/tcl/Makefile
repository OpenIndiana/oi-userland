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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         tcl
COMPONENT_VERSION=      8.5.12
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://prdownloads.sourceforge.net/tcl/
COMPONENT_SRC=          $(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:20ba7a10a30571983afd3599f19b441adb5222b21f1d2b27d0fba3ed8d4707c2
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libtcl

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_PREP_ACTION = \
	(cd $(SOURCE_DIR)/unix ; autoreconf -f; \
	 cd ../doc; \
            for i in *.n ; do manbase="$$(basename "$$i" .n)"; mv "$$i" "$${manbase}.1t"; done ; \
            for i in *.3 ; do manbase="$$(basename "$$i" .3)"; mv "$$i" "$${manbase}.3tcl"; done) 

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

#This macro will help to look for the configure 
#file at the pointed location 
CONFIGURE_SCRIPT = $(SOURCE_DIR)/unix/configure

CONFIGURE_OPTIONS	+= --enable-shared
CONFIGURE_OPTIONS	+= --enable-man-symlinks
CONFIGURE_OPTIONS	+= --enable-threads
CONFIGURE_OPTIONS.64	+= --enable-64bit

COMPONENT_TEST_TARGETS = test

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(PROTOUSRLIBDIR)/tclConfig.sh 

$(PROTOUSRLIBDIR)/tclConfig.sh:		$(INSTALL_32)	
					sed -f $(COMPONENT_DIR)/files/tclsed $(PROTOUSRLIBDIR)/tclConfig.sh > \
						$(PROTOUSRLIBDIR)/tclConfig.sh.new
					$(MV) $(PROTOUSRLIBDIR)/tclConfig.sh.new $(PROTOUSRLIBDIR)/tclConfig.sh
					$(CHMOD) 555 $(PROTOUSRLIBDIR)/tclConfig.sh

test: 		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
