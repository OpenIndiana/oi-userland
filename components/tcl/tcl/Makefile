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
# Copyright (c) 2020, Michal Nowak
# Copyright (c) 2023, Klaus Ziegler
#

USE_COMMON_TEST_MASTER= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         tcl
COMPONENT_VERSION=      8.6.13
COMPONENT_REVISION=     1
COMPONENT_MINOR_VERSION= $(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\)\.\([0-9]\+\)\.[0-9]\+/\1.\2/')
COMPONENT_SUMMARY=		Tcl - portable scripting environment
COMPONENT_DESCRIPTION=	Tcl is a dynamic programming language used in web and desktop applications, networking, administration, testing and many more applications
COMPONENT_PROJECT_URL=	https://core.tcl-lang.org/
COMPONENT_SRC=          $(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-core$(COMPONENT_VERSION)-src.tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c61f0d6699e2bc7691f119b41963aaa8dc980f23532c4e937739832a5f4a6642
COMPONENT_ARCHIVE_URL=  https://prdownloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			runtime/tcl-8
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=	BSD-like
COMPONENT_LICENSE_FILE=	license.terms

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += COMPONENT_MINOR_VERSION=$(COMPONENT_MINOR_VERSION)

COMPONENT_PREP_ACTION = \
	(cd $(SOURCE_DIR)/unix ; autoreconf -f; \
	 cd ../doc; \
            for i in *.n ; do manbase="$$(basename "$$i" .n)"; mv "$$i" "$${manbase}.1t"; done ; \
            for i in *.3 ; do manbase="$$(basename "$$i" .3)"; mv "$$i" "$${manbase}.3tcl"; done)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(SOURCE_DIR)/unix/configure

CONFIGURE_OPTIONS	+= --enable-shared
CONFIGURE_OPTIONS	+= --enable-man-symlinks
CONFIGURE_OPTIONS	+= --enable-threads
CONFIGURE_OPTIONS	+= --enable-64bit
ifeq ($(strip $(MACH)),sparc)
CONFIGURE_OPTIONS	+= --enable-64bit-vis
endif

install:	$(INSTALL_64) $(PROTOUSRLIBDIR)/$(MACH64)/tclConfig.sh

$(PROTOUSRLIBDIR)/$(MACH64)/tclConfig.sh:	$(INSTALL_64)
	sed -f $(COMPONENT_DIR)/files/tclsed $(PROTOUSRLIBDIR)/$(MACH64)/tclConfig.sh > \
		$(PROTOUSRLIBDIR)/$(MACH64)/tclConfig.sh.new
	$(MV) $(PROTOUSRLIBDIR)/$(MACH64)/tclConfig.sh.new $(PROTOUSRLIBDIR)/$(MACH64)/tclConfig.sh
	$(CHMOD) 555 $(PROTOUSRLIBDIR)/$(MACH64)/tclConfig.sh

# if test does not run the first, try second time, then it
# will show no diffs - some kind of a ping pong play.
COMPONENT_TEST_TARGETS= test
COMPONENT_TEST_TRANSFORMS= \
	'-n' \
	'-e "/^LD_LIBRARY_PATH/d"' \
	'-e "/all\.tcl/p"' \
	'-e "/Files/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
