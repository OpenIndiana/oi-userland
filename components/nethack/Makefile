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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(USRBINDIR)

COMPONENT_NAME=		nethack
COMPONENT_VERSION=	3.6.0
COMPONENT_PROJECT_URL=	http://www.nethack.org/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(subst .,,$(COMPONENT_VERSION))-src.tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1ade698d8458b8d87a4721444cb73f178c74ed1b6fde537c12000f8edf2cb18a
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_ANITYA_ID=	8309

TPNO=			27856

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

# This file contains the configuration we need
COMPONENT_POST_UNPACK_ACTION = $(CP) files/solaris $(SOURCE_DIR)/sys/unix/hints

# Need to use Makefiles in the sys/unix directory and copy them into various
# other directories.
#
COMPONENT_PREP_ACTION= (cd $(SOURCE_DIR)/sys/unix; sh setup.sh hints/solaris)

COMPONENT_BUILD_TARGETS = all
COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += TOP_CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LFLAGS="$(CC_BITS)"

# Uncomment out a few lines in the resources file
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -e 's/^!\(NetHack.tomb\)/\1/' -e 's/^!\(NetHack.pet\)/\1/' \
		-e 's/^!\(NetHack.pilemark\)/\1/' \
		$(COMPONENT_SRC)/win/X11/NetHack.ad \
		> $(PROTO_DIR)/usr/lib/nethack/NetHack.ad

PKG_PROTO_DIRS += $(COMPONENT_SRC)/doc

REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += x11/compatibility/links-xorg
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
