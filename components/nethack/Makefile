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
#

include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		nethack
COMPONENT_VERSION=	3.4.3
COMPONENT_PROJECT_URL=	http://www.nethack.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-343-src.tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bb39c3d2a9ee2df4a0c8fdde708fbc63740853a7608d2f4c560b488124866fe4
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	utility/nethack

TPNO=			9239

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

# Need to use Makefiles in the sys/unix directory and copy them into various
# other directories.
#
COMPONENT_PREP_ACTION= (cd $(SOURCE_DIR)/sys/unix ; sh setup.sh)

COMPONENT_INSTALL_ARGS += CHOWN=true
COMPONENT_INSTALL_ARGS += CHGRP=true
COMPONENT_INSTALL_ARGS += ROOT=$(PROTO_DIR)

# Nethack's build infrastructure doesn't let you easily override CFLAGS.
# Luckily, all the source files live in the same location relative to the
# include directory, so we can just stuff a -I into CFLAGS matching what's
# there in the Makefiles.  And we have to force this to be overridden by
# putting -e into MAKEFLAGS.
COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS) -I../include"
COMPONENT_BUILD_ENV += LFLAGS="$(CC_BITS)"
COMPONENT_BUILD_ENV += MAKEFLAGS=-e
COMPONENT_INSTALL_ENV += CC=$(CC)
COMPONENT_INSTALL_ENV += CFLAGS="$(CFLAGS) -I../include"
COMPONENT_INSTALL_ENV += LFLAGS="$(CC_BITS)"
COMPONENT_INSTALL_ENV += MAKEFLAGS=-e

PKG_PROTO_DIRS += $(COMPONENT_SRC)/doc

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)
	sed -e 's/^!\(NetHack.tomb\)/\1/' -e 's/^!\(NetHack.pet\)/\1/' \
		-e 's/^!\(NetHack.tile_file\)/\1/' \
		$(COMPONENT_SRC)/win/X11/NetHack.ad \
		> $(PROTO_DIR)/usr/lib/nethack/NetHack.ad

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/compatibility/links-xorg
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
