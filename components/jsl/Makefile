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

# Preferred compiler set to gcc and not Studio as on Sparc architecture
# some assembler code is required for locking which fails to compile on
# solaris, when using gcc this is inlined (see jslock.c)
COMPILER =	gcc
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		jsl
COMPONENT_VERSION=	0.3.0
COMPONENT_PROJECT_URL=	http://www.javascriptlint.com
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:86f16792d71fc59b96f65eca65b1b7466dc046efe6d5ac04c6632f1315e83cfa
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1476

TPNO=			10774

BUILD_STYLE= justmake
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS += -f src/Makefile
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += COPTFLAGS="$(gcc_OPT)"
COMPONENT_BUILD_TARGETS += all

COMPONENT_INSTALL_ARGS += -f src/Makefile
COMPONENT_INSTALL_ARGS += BINDIR=$(PROTOUSRBINDIR64)
COMPONENT_INSTALL_ARGS += USRSHAREDIR=$(PROTOUSRSHAREDIR)
COMPONENT_INSTALL_ARGS += INSTALL="$(INSTALL)"
COMPONENT_INSTALL_ARGS += MKDIR="$(MKDIR)"

COMPONENT_TEST_DIR =		$(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =            $(PERL) ./run_tests.pl
COMPONENT_TEST_TARGETS =        $(PROTOUSRBINDIR64)/jsl

test:		install $(TEST_64)

# Add install dependency as above when system test targets are implemented.

REQUIRED_PACKAGES += system/library/math
