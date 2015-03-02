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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		getopt
COMPONENT_VERSION=	1.1.6
COMPONENT_PROJECT_URL=	http://frodo.looijaard.name/project/getopt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d0bf1dc642a993e7388a1cddfb9409bed375c21d5278056ccca3a0acd09dc5fe
COMPONENT_ARCHIVE_URL=	http://frodo.looijaard.name/system/files/software/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-getopt

TPNO=			21550

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# getopt doesn't use configure, override the hard-wired values in the Makefile.
CC += "$(CC_BITS)"
COMPONENT_BUILD_ARGS+=	CC="$(CC)"
COMPONENT_BUILD_ARGS+=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS+=	LIBCGETOPT=0

COMPONENT_INSTALL_ARGS+=	prefix=/usr/gnu
COMPONENT_INSTALL_ARGS+=	mandir=/usr/gnu/share/man
COMPONENT_INSTALL_ARGS+=	CC="$(CC)"
COMPONENT_INSTALL_ARGS+=	CFLAGS="$(CFLAGS)"

# Stupid source tarball distribution contains two .o files.
COMPONENT_POST_UNPACK_ACTION= \
	$(RM) $(COMPONENT_SRC)/gnu/*.o

COMPONENT_TEST_ENV +=		PATH=$(BUILD_DIR_$(BITS)):$(PATH)
COMPONENT_TEST_TARGETS =	test

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)


REQUIRED_PACKAGES += system/library
