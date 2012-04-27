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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		which
COMPONENT_VERSION=	2.16
COMPONENT_PROJECT_URL=	http://www.xs4all.nl/~carlo17/which/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0ac8502e9985a3ac6b0e2aa4f2a60f91cad0dc0cca6dc9c1c142ebba4b8dd664
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/which/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX    =	/usr/gnu
CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=	--disable-iberty
CONFIGURE_OPTIONS  +=	--disable-dependency-tracking
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
