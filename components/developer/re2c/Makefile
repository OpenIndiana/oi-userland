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
#
BUILD_BITS=				64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			re2c
COMPONENT_VERSION=		2.0.3
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
COMPONENT_FMRI=			developer/lexer/re2c
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=	https://re2c.org
COMPONENT_ARCHIVE_HASH=	sha256:b2bc1eb8aaaa21ff2fcd26507b7e6e72c5e3d887e58aa515c2155fb17d744278
COMPONENT_ARCHIVE_URL=	https://github.com/skvadrik/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		public domain
COMPONENT_LICENS_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/common.mk

export PATH=$(PATH.gnu)

# Needed to get the tests to run successfully.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
