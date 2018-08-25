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
# Copyright (c) 2017, Aurelien Larcher
# Copyright (c) 2018, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libexpat
COMPONENT_VERSION=	2.2.6
COMPONENT_VERSION_U=	$(shell echo $(COMPONENT_VERSION) | tr . _)
COMPONENT_FMRI=		library/expat
COMPONENT_SUMMARY=	libexpat - XML parser library
COMPONENT_DESCRIPTION=	A fast, non-validating, stream-oriented XML parsing library	
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_PROJECT_URL=	https://libexpat.github.io
COMPONENT_SRC_NAME=	expat
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:17b43c2716d521369f82fc2dc70f359860e90fa440bea65b3b85f0b246ea81f2
COMPONENT_ARCHIVE_URL= \
    https://github.com/libexpat/libexpat/releases/download/R_$(COMPONENT_VERSION_U)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	expat license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS+= --disable-static

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS= \
	'-e "s/^\# //" ' \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/PASS/p" '  \
	'-e "/SKIP/p" '  \
	'-e "/XFAIL/p" ' \
	'-e "/FAIL/p" '  \
	'-e "/XPASS/p" ' \
	'-e "/ERROR/p" ' \

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
