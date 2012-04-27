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

COMPONENT_NAME=		slrn
COMPONENT_VERSION=	0.9.9
COMPONENT_SUBVERSION=	p1
HUMAN_VERSION=		$(COMPONENT_VERSION)$(COMPONENT_SUBVERSION)
COMPONENT_PROJECT_URL=	http://slrn.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3a896f42b78c32252878fd291b21d6482d466921b68ab97f7d8cbadf4a76b533
COMPONENT_ARCHIVE_URL=	ftp://space.mit.edu/pub/davis/slrn/$(COMPONENT_ARCHIVE)
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).1

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)
CONFIGURE_SCRIPT = $(@D)/configure

# slrn configure test for 'mkdir -p' functionality doesn't like Solaris
# implementation (GNU mkdir will understand --version option).
PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-server-file=/etc/nntpserver
CONFIGURE_OPTIONS +=	--with-slrnpull=/var/spool/slrnpull
CONFIGURE_OPTIONS +=	--enable-spool
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
