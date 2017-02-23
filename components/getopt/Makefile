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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		getopt
COMPONENT_VERSION=	1.1.6
COMPONENT_PROJECT_URL=	http://frodo.looijaard.name/project/getopt/
COMPONENT_ARCHIVE_HASH=	\
    sha256:d0bf1dc642a993e7388a1cddfb9409bed375c21d5278056ccca3a0acd09dc5fe
COMPONENT_ARCHIVE_URL=	http://frodo.looijaard.name/system/files/software/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-getopt
COMPONENT_ANITYA_ID=	13265

TPNO=			21550

BUILD_STYLE= justmake
SYSTEM_TEST_TARGET= $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

# getopt doesn't use configure, override the hard-wired values in the Makefile.
LDFLAGS += $(CC_BITS)
COMPONENT_BUILD_ARGS+=	CC="$(CC)"
COMPONENT_BUILD_ARGS+=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS+=	LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ARGS+=	LIBCGETOPT=0

COMPONENT_INSTALL_ARGS+=	prefix="$(USRGNUDIR)"
COMPONENT_INSTALL_ARGS+=	mandir="$(GNUSHAREMAN)"
COMPONENT_INSTALL_ARGS+=	CC="$(CC)"
COMPONENT_INSTALL_ARGS+=	CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ARGS+=	LDFLAGS="$(LDFLAGS)"

# Stupid source tarball distribution contains two .o files.
COMPONENT_POST_UNPACK_ACTION= \
	$(RM) $(COMPONENT_SRC)/gnu/*.o

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\./getopt|getopt|g" ' \
	'-e "s|/usr/gnu/bin/getopt|getopt|g" ' \
	'-e "s|\./run-tests.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make\[1\].*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

COMPONENT_TEST_ENV +=		PATH=$(BUILD_DIR_$(BITS)):$(GNUBIN):$(USRBINDIR)
COMPONENT_TEST_TARGETS =	test

COMPONENT_SYSTEM_TEST_ENV +=	PATH=$(GNUBIN):$(USRBINDIR)
COMPONENT_SYSTEM_TEST_CMD =	./run-tests
COMPONENT_SYSTEM_TEST_ARGS =	$(GNUBIN)/getopt
COMPONENT_SYSTEM_TEST_TARGETS =
