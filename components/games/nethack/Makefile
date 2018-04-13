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
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nethack
COMPONENT_VERSION=	3.6.0
COMPONENT_PROJECT_URL=	https://www.nethack.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-360-src.tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1ade698d8458b8d87a4721444cb73f178c74ed1b6fde537c12000f8edf2cb18a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		games/nethack
COMPONENT_LICENSE=      Nethack
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=      A single-player dungeon exploration game
COMPONENT_DESCRIPTION=	Nethack is a turn-based single-player dungeon exploration game related to Hack and Rogue.  The primary interface is a pseudo-graphical display rendered in text in a terminal, and controlled by the keyboard.
COMPONENT_CLASSIFICATION="Applications/Games"

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# Need to use Makefiles in the sys/unix directory and copy them into various
# other directories.
#
COMPONENT_PREP_ACTION= (cd $(SOURCE_DIR)/sys/unix ; sh setup.sh)

COMPONENT_INSTALL_ARGS += CHOWN=true
COMPONENT_INSTALL_ARGS += CHGRP=true
COMPONENT_INSTALL_ARGS += ROOT=$(PROTO_DIR)

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += CC=$(CC)
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ENV += LFLAGS="$(CFLAGS)"

PKG_PROTO_DIRS += $(COMPONENT_SRC)/doc
PKG_PROTO_DIRS += $(COMPONENT_SRC)/sys/unix

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)
	sed -e 's/^!\(NetHack.tomb\)/\1/' -e 's/^!\(NetHack.pet\)/\1/' \
		-e 's/^!\(NetHack.tile_file\)/\1/' \
		$(COMPONENT_SRC)/win/X11/NetHack.ad \
		> $(PROTO_DIR)/usr/lib/nethack/NetHack.ad

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += developer/lexer/flex
