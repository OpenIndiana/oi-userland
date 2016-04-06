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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rsyslog
COMPONENT_VERSION=	7.4.10
COMPONENT_REVISION=	2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://rsyslog.com/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ab1d26da2bfd38db34dd991a9c5d93034ef1373d01f9d5a0923bb0d4802b9fbe
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rsyslog

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
                                        autoreconf -f -i)

CONFIGURE_SBINDIR.$(BITS) = $(CONFIGURE_LIBDIR.$(BITS))/rsyslog

CONFIGURE_OPTIONS +=    --enable-imsolaris
CONFIGURE_OPTIONS +=    --enable-cached-man-pages
CONFIGURE_OPTIONS +=    --enable-mail
#CONFIGURE_OPTIONS +=    --enable-gssapi_krb5
CONFIGURE_OPTIONS +=    --enable-gnutls
CONFIGURE_OPTIONS +=    --disable-klog

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

include $(WS_TOP)/make-rules/depend.mk
