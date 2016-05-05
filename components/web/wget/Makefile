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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wget
COMPONENT_VERSION=	1.17.1
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/wget/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fe559b61eb9cc01635ac6206a14e02cb51591838c35fa83c7a4aacae0bdd97c9
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/wget/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/wget

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# Enforce openssl (--with-ssl=openssl) instead of default gnutls
# (--with-ssl) as wget doesn't work for secure connections with gnutls. 
# Set PATH to find /usr/perl5/bin/pod2man, so that the man page wget.1
# can be automatically generated
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--with-ssl=openssl
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	PATH="$(PATH):/usr/perl5/bin"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# TOTAL: 85
# PASS:  82
# SKIP:  3
# XFAIL: 0
# FAIL:  0
# XPASS: 0
test:		$(TEST_32_and_64)
