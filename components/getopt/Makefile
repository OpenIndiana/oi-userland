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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		getopt
COMPONENT_VERSION=	1.1.5
COMPONENT_PROJECT_URL=	http://software.frodo.looijaard.name/getopt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:11893276b94b1629606ab75772143918a5713259950fbf4216288e246f19fbb6
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-getopt

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

# getopt doesn't use configure, override the hard-wired values in the Makefile.
COMPONENT_BUILD_ARGS+=	CC="$(CC) $(CC_BITS)"
COMPONENT_BUILD_ARGS+=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS+=	LIBCGETOPT=0

COMPONENT_INSTALL_ARGS+=	prefix=/usr/gnu
COMPONENT_INSTALL_ARGS+=	mandir=/usr/gnu/share/man
COMPONENT_INSTALL_ARGS+=	CC="$(CC) $(CC_BITS)"
COMPONENT_INSTALL_ARGS+=	CFLAGS="$(CFLAGS)"

# Stupid source tarball distribution contains two .o files.
COMPONENT_POST_UNPACK_ACTION= \
	$(RM) $(COMPONENT_SRC)/gnu/*.o

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
