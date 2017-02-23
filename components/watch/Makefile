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
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		procps-ng
COMPONENT_VERSION=	3.3.11
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/procps-ng/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e9493169a2d2adc0bc045538707310c8e877b385e4e296143b62607d2bb044ed
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/Production/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	utility/watch
COMPONENT_ANITYA_ID=	3708

TPNO=			27264

INSTALL_TARGET= build
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk


CFLAGS +=			-I$(USRINCDIR)/ncurses

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=		V=1

# Don't try to link watch with .../proc/libprocps.la as it's not needed.
COMPONENT_BUILD_ARGS +=		LDADD=

COMPONENT_BUILD_TARGETS =	watch

PKG_PROTO_DIRS += $(BUILD_DIR_64)

REQUIRED_PACKAGES +=	library/ncurses
