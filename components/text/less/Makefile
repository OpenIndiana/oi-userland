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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2020, Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		less
COMPONENT_VERSION=	710
COMPONENT_SUMMARY=	Pager program similar to more
COMPONENT_DESCRIPTION=	The package provides less, \
						a file pager (a memory-efficient utility for displaying text one screenful at a time).
COMPONENT_PROJECT_URL=	https://www.greenwoodsoftware.com/less/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d1008fb78dcae1323ddab664bcb352a61f022b1b131bd8018548e021d975ec7a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/less
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_LICENSE=	Less
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Make gcc-14 happy
CFLAGS += -Wno-error=incompatible-pointer-types
CFLAGS += -I/usr/include/pcre

# Fix 64-bit linking done via compiler.
CC += $(CC_BITS)

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --with-regex=pcre2

ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
