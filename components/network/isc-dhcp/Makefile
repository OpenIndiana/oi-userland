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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		isc-dhcp
COMPONENT_VERSION=	4.3.6-P1
IPS_COMPONENT_VERSION=	4.3.6.1
COMPONENT_FMRI=		service/network/dhcp/isc-dhcp
COMPONENT_SUMMARY=	ISC DHCP Server and Relay Agent
COMPONENT_CLASSIFICATION=System/Services
COMPONENT_SRC_NAME=	dhcp
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://www.isc.org/software/dhcp/
COMPONENT_ARCHIVE_URL=  \
    http://ftp.isc.org/isc/dhcp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:2fd177bef02856f05fe17713ced9bfcc7d94f14c933c15f2f2fbedc9cc57a3c3
COMPONENT_BUGDB=	service/dhcp-server

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Parallel build fails
COMPONENT_BUILD_ARGS =

CONFIGURE_SCRIPT	= $(@D)/configure
COMPONENT_PRE_CONFIGURE_ACTION+=	$(CP) -R $(SOURCE_DIR)/* $(@D)/

CFLAGS+= -std=gnu89 -D_XOPEN_SOURCE=500 -D__EXTENSIONS__

CONFIGURE_OPTIONS  +=	--sysconfdir=$(ETCDIR)/inet
CONFIGURE_OPTIONS  +=	--sbindir=$(USRLIBDIR)/inet
CONFIGURE_OPTIONS  +=	--bindir=$(USRSBINDIR)
CONFIGURE_OPTIONS  +=	--enable-use-sockets
CONFIGURE_OPTIONS  +=	--enable-ipv4-pktinfo


# Disable message in omapip/errwarn.c.
CPPFLAGS  +=	        -DNOMINUM
CONFIGURE_OPTIONS  +=   CPPFLAGS="$(CPPFLAGS)"

LDFLAGS += -lnsl -lsocket

# ISC dhcp contains bind tarball. As it is configured in build stage
# we have to pass CFLAGS and LDFLAGS to its configure at build time.
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_TEST_DIR =	$(@D)

build:		$(BUILD_64)

install:	build $(INSTALL_64) $(PROTO_DIR)/dhcpd.leases

test:	$(TEST_64)

$(PROTO_DIR)/dhcpd.leases:	$(INSTALL_64)
	$(TOUCH) $@

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
