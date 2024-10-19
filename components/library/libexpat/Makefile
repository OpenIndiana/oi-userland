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
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS= 64_and_32
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		expat
COMPONENT_VERSION=	2.6.3
COMPONENT_REVISION=	1
COMPONENT_VERSION_U=	$(subst .,_,$(COMPONENT_VERSION))
COMPONENT_SUMMARY=	libexpat - XML parser library
COMPONENT_DESCRIPTION=	A fast, non-validating, stream-oriented XML parsing library	
COMPONENT_PROJECT_URL=	https://libexpat.github.io
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.lz
COMPONENT_ARCHIVE_HASH=	sha256:b8713f2d3cb3a3eee9ab763f66aa68f93cf6820bccf1272a682cf79b99ae6fbc
COMPONENT_ARCHIVE_URL=	https://github.com/libexpat/libexpat/releases/download/R_$(COMPONENT_VERSION_U)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/expat
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_FMRI.$(COMPONENT_NAME)-32 =		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.$(COMPONENT_NAME)-32 =	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --disable-static

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) ;

# Workaround for the following expat bug:
# https://github.com/libexpat/libexpat/issues/501
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(GSED) -i -e '/^get_filename_component.*CMAKE/{n; p;}' $(PROTOUSRLIBDIR64)/cmake/$(COMPONENT_SRC)/expat.cmake ; \
	$(GSED) -i -e 's/$(MACH64)/lib\/&/' $(PROTOUSRLIBDIR64)/cmake/$(COMPONENT_SRC)/expat-noconfig.cmake ;

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
