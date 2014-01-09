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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tar
COMPONENT_VERSION=	1.27.1
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/tar/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:9b0fb3ce8512059337add0da5f8f0f7d7647f2201f5ece24581d620ea60337c6
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/tar/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gtar

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# workaround for CR 6998994
sparc_COPTFLAG = -xO2

# Enforce tar binary to standard path
CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin

# Use ssh (rather than rsh) for remote commands.
CONFIGURE_ENV += "RSH=/usr/bin/ssh"

CONFIGURE_OPTIONS +=	--with-rmt=/usr/sbin/rmt
CONFIGURE_OPTIONS +=	--libexecdir=/usr/sbin
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)" 

COMPONENT_BUILD_TARGETS = all

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
