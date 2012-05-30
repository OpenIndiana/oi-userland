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

COMPONENT_NAME=		sudo
SRC_VERSION=	1.8.4
SRC_PATCH_VERSION=	5
COMPONENT_VERSION=	$(SRC_VERSION).$(SRC_PATCH_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(SRC_VERSION)p$(SRC_PATCH_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:cf41ea1ada17c0dfbd8480dd9dc800999e0db9f2972ffa8f7a2944751ad32aba
COMPONENT_ARCHIVE_URL=	http://www.sudo.ws/sudo/dist/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.sudo.ws/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_ENV +=	"CC=$(CC)"
CONFIGURE_ENV +=	"CFLAGS=$(CFLAGS)"
CONFIGURE_ENV +=	"CXX=$(CXX)"
CONFIGURE_ENV +=	"MAKE=$(GMAKE)"

CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-project
CONFIGURE_OPTIONS +=	--with-timedir=/system/volatile/sudo
CONFIGURE_OPTIONS +=	--with-pam --with-pam-login
CONFIGURE_OPTIONS +=	--with-tty-tickets
CONFIGURE_OPTIONS +=	--without-insults
CONFIGURE_OPTIONS +=	--without-lecture
CONFIGURE_OPTIONS +=	--with-ignore-dot
CONFIGURE_OPTIONS +=	--with-bsm-audit
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/sudo

COMPONENT_BUILD_ENV +=	CC=$(CC) CXX=$(CXX)
COMPONENT_BUILD_ENV +=	"CFLAGS=$(CFLAGS)"

COMPONENT_INSTALL_TARGETS = install

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
