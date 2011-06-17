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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cmake
COMPONENT_VERSION=	2.6.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:48d33afaf23d40f2ea9aa2f5018c7213983222c2
COMPONENT_ARCHIVE_URL=	http://www.cmake.org/files/v2.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.cmake.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# Need to remove this option from LD_OPTIONS (only affects sparc build);
# it causes a SegFault failure in kwsys/testSystemInformation
# when testing on sparc
LD_MAP_NOEXBSS=

LDFLAGS +=	$($(COMPILER)_NORUNPATH)

# We need these in the environment, although they are already passed
# as CONFIGURE_OPTIONS; otherwise the correct compilers are not used
CONFIGURE_ENV +=	CC="$(CC)"	
CONFIGURE_ENV +=	CXX="$(CXX)"	
CONFIGURE_ENV +=	LDFLAGS="$(LDFLAGS)"	
CONFIGURE_ENV +=	MAKE="$(GMAKE)"	

# CmakeCache-txt is created by configure, so we need to patch
# it after configure
COMPONENT_POST_CONFIGURE_ACTION =	( cd $(BUILD_DIR_$(BITS)); \
	$(GPATCH) $(GPATCH_FLAGS) < \
	$(COMPONENT_DIR)/patches-post-config/CmakeCache-txt.patch )

COMPONENT_BUILD_ENV +=	CC="$(CC)"	
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"	
COMPONENT_BUILD_ENV +=	LDFLAGS="$(LDFLAGS)"	
COMPONENT_BUILD_ENV +=	MAKE="$(GMAKE)"	
COMPONENT_BUILD_TARGETS =	all

COMPONENT_TEST_TARGETS =	test

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

# expected failures: curl, complex, complexOneConfig
test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
