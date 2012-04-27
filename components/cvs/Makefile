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

# we hit parfait bug 12333159 in a case statement, so disable parfait
# until we can move to clang
PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cvs
COMPONENT_VERSION=	1.12.13
COMPONENT_PROJECT_URL=	http://www.nongnu.org/cvs/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:78853613b9a6873a30e1cc2417f738c330e75f887afdaf7b3d0800cb19ca515e
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/non-gnu/cvs/source/feature/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS += -D__ATTRIBUTE_DISABLED
CONFIGURE_OPTIONS  +=	--with-external-zlib
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

# "check" is not working yet.  It's asking for a password.
COMPONENT_TEST_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_TEST_TARGETS = localcheck

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
