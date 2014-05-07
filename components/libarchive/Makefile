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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libarchive
COMPONENT_VERSION=	3.0.4
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://github.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:76e8d7c7b100ec4071e48c1b7d3f3ea1d22b39db3e45b7189f75b5ff4df90fac
COMPONENT_ARCHIVE_URL=	\
    $(COMPONENT_PROJECT_URL)downloads/libarchive/libarchive/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libarchive

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

# libarchive's Makefile hard-codes some gcc-only flags in COMMON_CFLAGS, then
# appends CFLAGS to that.  Reset the former here so we can build with Studio.
COMPONENT_BUILD_ARGS +=	COMMON_CFLAGS=''
COMPONENT_BUILD_ARGS +=	CFLAGS="$(CFLAGS)"
COMPONENT_TEST_ARGS +=	COMMON_CFLAGS=''
COMPONENT_TEST_ARGS +=	CFLAGS="$(CFLAGS)"

# We need GNU awk for the following to work; hence the PATH tweak.
COMPONENT_PREP_ACTION = \
    (cd $(@D)/doc/man ; rm *.[135] ; env PATH=/usr/gnu/bin:$$PATH gmake all)
PKG_PROTO_DIRS += $(COMPONENT_SRC)/doc/man

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
