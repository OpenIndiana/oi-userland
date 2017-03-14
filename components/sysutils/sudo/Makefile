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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sudo
SRC_VERSION=		1.8.19
SRC_PATCH_VERSION=	2
COMPONENT_VERSION=	$(SRC_VERSION).$(SRC_PATCH_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(SRC_VERSION)p$(SRC_PATCH_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:237e18e67c2ad59ecacfa4b7707198b09fcf84914621585a9bc670dcc31a52e0
COMPONENT_ARCHIVE_URL=	http://www.sudo.ws/sudo/dist/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig	
COMPONENT_PROJECT_URL=  http://www.sudo.ws/
COMPONENT_BUGDB=	utility/sudo

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_ENV +=	MAKE=$(GMAKE)

CONFIGURE_OPTIONS +=	--disable-nls
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-project
CONFIGURE_OPTIONS +=	--with-rundir=/var/run/sudo
CONFIGURE_OPTIONS +=	--with-pam 
CONFIGURE_OPTIONS +=	--with-pam-login
CONFIGURE_OPTIONS +=	--disable-pam-session
CONFIGURE_OPTIONS +=	--with-tty-tickets
CONFIGURE_OPTIONS +=	--without-insults
CONFIGURE_OPTIONS +=	--without-lecture
CONFIGURE_OPTIONS +=	--with-ignore-dot
CONFIGURE_OPTIONS +=	--without-bsm-audit
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/sudo
CONFIGURE_OPTIONS +=	--with-mdoc

COMPONENT_BUILD_ENV +=	CC="$(CC)"
COMPONENT_BUILD_ENV +=	CXX="$(CXX)"
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_TARGETS = install
COMPONENT_INSTALL_ARGS += INSTALL_OWNER=

# Enable aslr for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
