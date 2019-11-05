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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnugo
COMPONENT_VERSION=	3.8
COMPONENT_REVISION=	1
COMPONENT_FMRI=		games/gnugo
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/gnugo/
COMPONENT_SUMMARY=	gnugo - program that plays the game of Go.
COMPONENT_DESCRIPTION=	GNU Go is a free program that plays the game of Go.
COMPONENT_CLASSIFICATION=Applications/Games
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:da68d7a65f44dcf6ce6e4e630b6f6dd9897249d34425920bfdd4e07ff1866a72
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gnugo/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	gnugo.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
