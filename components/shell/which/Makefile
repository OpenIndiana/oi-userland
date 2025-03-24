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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		which
COMPONENT_VERSION=	2.23
COMPONENT_SUMMARY=	GNU which - Utility to show the full path of (shell) commands
COMPONENT_PROJECT_URL=	https://savannah.gnu.org/projects/which/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a2c558226fc4d9e4ce331bd2fd3c3f17f955115d2c00e447618a4ef9978a2a73
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/which/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		shell/which
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION += ( $(RM) $(PROTOUSRSHAREDIR)/info/dir );

CFLAGS += $(XPG6MODE)
CFLAGS += -DNEED_XMALLOC=1

CONFIGURE_PREFIX    = /usr/gnu
CONFIGURE_OPTIONS  += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  += --enable-year2038
CONFIGURE_OPTIONS  += --disable-iberty
CONFIGURE_OPTIONS  += --disable-dependency-tracking

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
