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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		iftop
COMPONENT_VERSION=	0.17
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.ex-parrot.com/~pdw/iftop/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d032547c708307159ff5fd0df23ebd3cfa7799c31536fa0aea1820318a8e0eac
COMPONENT_ARCHIVE_URL=	http://www.ex-parrot.com/~pdw/iftop/download/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

PATCH_LEVEL=	0

# without this we bus error on sparc. sadly I don't see any patches
# that might relate from the upstream (though maybe that's really
# "happily", as this is simpler)
studio_ALIGN.sparc.32=	-xmemalign=1i


IFTOP_LIBDIR=	/usr/gnu/lib
LDFLAGS +=	-L$(IFTOP_LIBDIR) -R$(IFTOP_LIBDIR)
CPPFLAGS +=	-I/usr/gnu/include -I/usr/include/ncurses
CONFIGURE_OPTIONS  +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS  +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
