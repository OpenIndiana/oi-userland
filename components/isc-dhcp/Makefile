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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		dhcp
COMPONENT_VERSION=	4.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-ESV-R1
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha1:64664b2fd3ce9e372785cbbef685f86ee3dcd53a
COMPONENT_ARCHIVE_URL=  http://ftp.isc.org/isc/dhcp/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=	--sysconfdir=$(ETCDIR)/inet
CONFIGURE_OPTIONS  +=	--sbindir=$(USRLIBDIR)/inet
CONFIGURE_OPTIONS  +=	--bindir=$(USRSBINDIR)
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS) -DUSE_SOCKETS"

build:		$(BUILD_32)

install:	build $(INSTALL_32) $(PROTO_DIR)/dhcpd.leases

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:	build
	@cd $(BUILD_DIR_32); $(MAKE) check

$(PROTO_DIR)/dhcpd.leases:	$(INSTALL_32)
	$(TOUCH) $@

include ../../make-rules/depend.mk
