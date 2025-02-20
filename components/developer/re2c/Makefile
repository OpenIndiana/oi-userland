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
# Copyright (c) 2015, 2020, Oracle and/or its affiliates.
# Copyright (c) 2020, Andreas Wacknitz
# Copyright (c) 2023, Friedrich Kink
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			re2c
COMPONENT_VERSION=		4.1
COMPONENT_SUMMARY=		re2c is a free and open-source lexer generator for C, C++ and Go.
COMPONENT_DESCRIPTION=	Its main goal is generating fast lexers: at least as \
	fast as their reasonably optimized hand-coded counterparts. Instead of \
	using traditional table-driven approach, re2c encodes the generated finite \
	state automata directly in the form of conditional jumps and comparisons. \
	The resulting programs are faster and often smaller than their table-driven analogues, \
	and they are much easier to debug and understand. re2c applies quite a few \
	optimizations in order to speed up and compress the generated code. \
	Another distinctive feature is its flexible interface: instead of assuming a \
	fixed program template, re2c lets the programmer write most of the interface code \
	and adapt the generated lexer to any particular environment.
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=	https://re2c.org
COMPONENT_ARCHIVE_HASH=	sha256:cd7d9bbadb3f04f20da25e20e155655de57beef48e0807266938069f0e322e8b
COMPONENT_ARCHIVE_URL=	https://github.com/skvadrik/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/lexer/re2c
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=		public domain
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

export PATH= $(PATH.gnu)

# Needed to get the tests to run successfully.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
