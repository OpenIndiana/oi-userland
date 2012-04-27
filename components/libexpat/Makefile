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

COMPONENT_NAME=		expat
COMPONENT_VERSION=	2.0.1
COMPONENT_PROJECT_URL=	http://expat.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:847660b4df86e707c9150e33cd8c25bc5cd828f708c7418e765e3e983a2e5e93
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/expat/expat/2.0.1/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

# To allow '__func__' usage in C++ code (runtestspp.cpp).
CXXFLAGS += $(studio_FEATURES_EXTENSIONS)

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS) $(CPP_LARGEFILES)"
CONFIGURE_OPTIONS += CXXFLAGS="$(CXXFLAGS)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
