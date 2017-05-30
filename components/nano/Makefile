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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		nano
COMPONENT_VERSION=	2.8.4
COMPONENT_PROJECT_URL=	http://www.nano-editor.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:78a2f3b3f6b500fad995c5e207d2816cbd6b531154aa2a3a2bd50c8fdf7dc57f
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dist/v2.8/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	2046

TPNO=			35626

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Ensure ancient autoconf scripts are overwritten with fixed versions that
# properly detect SunOS 5.x hosts.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv)

CPPFLAGS += -I$(USRINCDIR)/ncurses
CFLAGS += -I$(USRINCDIR)/ncurses

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += text/groff
