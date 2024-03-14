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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libedit
COMPONENT_VERSION_DATE=	20230828
COMPONENT_VERSION=	3.1.$(COMPONENT_VERSION_DATE)
COMPONENT_SUMMARY=	Libedit - Command line editor library
COMPONENT_PROJECT_URL=	https://www.thrysoee.dk/editline/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_DATE)-3.1
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4ee8182b6e569290e7d1f44f0f78dac8716b35f656b76528f699c69c98814dad
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libedit
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Uses GNU awk
PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -f)

CFLAGS += $(XPG6MODE)

CONFIGURE_OPTIONS += --disable-static

# Build dependencies
REQUIRED_PACKAGES += text/gawk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
