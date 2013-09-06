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

COMPONENT_NAME=		rsyslog
COMPONENT_VERSION=	6.2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://rsyslog.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f8869a1c25d0dd9ff04468743969ffc9ff89c6f7afa3046f77f91c3982543cc1
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rsyslog

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# A normal 64-bit build would result in /usr/lib/$(MACH64)/rsyslog but since we
# have a self-contained eco-system, simplify things for customers and just use
# /usr/lib/rsyslog .
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_LIBDIR.32)

CONFIGURE_OPTIONS +=    --enable-imsolaris
CONFIGURE_OPTIONS +=    --enable-mail
CONFIGURE_OPTIONS +=    --enable-gssapi_krb5
CONFIGURE_OPTIONS +=    --enable-gnutls
CONFIGURE_OPTIONS +=    --disable-klog
CONFIGURE_OPTIONS +=    --sbindir=/usr/lib/rsyslog

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

include ../../make-rules/depend.mk
