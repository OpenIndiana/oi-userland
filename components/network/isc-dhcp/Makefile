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
# Copyright (c) 2011, 2019, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		isc-dhcp
COMPONENT_VERSION=	4.4.2
COMPONENT_REVISION=	2
IPS_COMPONENT_VERSION=	4.4.2.0.0
COMPONENT_FMRI=		service/network/dhcp/isc-dhcp
COMPONENT_SUMMARY=	ISC DHCP Server and Relay Agent
COMPONENT_CLASSIFICATION=	System/Services
COMPONENT_SRC_NAME=	dhcp
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://www.isc.org/software/dhcp/
COMPONENT_ARCHIVE_URL=  \
	http://ftp.isc.org/isc/dhcp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:1a7ccd64a16e5e68f7b5e0f527fd07240a2892ea53fe245620f4f5f607004521
COMPONENT_LICENSE=	MPL v2.0
COMPONENT_LICENSE_FILE=	LICENSE

# We don't ship ATF/Kyua
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lnsl -lsocket

# Parallel build fails in bind
COMPONENT_BUILD_ARGS =

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=	--sysconfdir=$(ETCDIR)/inet
CONFIGURE_OPTIONS  +=	--sbindir=$(USRLIBDIR)/inet
CONFIGURE_OPTIONS  +=	--bindir=$(USRSBINDIR)
CONFIGURE_OPTIONS  +=	--enable-use-sockets
CONFIGURE_OPTIONS  +=	--enable-ipv4-pktinfo
CONFIGURE_OPTIONS  +=	--srcdir=$(BUILD_DIR_$(BITS))

COMPONENT_POST_BUILD_ACTION = $(MAKE) -C $(BUILD_DIR_64)/keama
COMPONENT_POST_INSTALL_ACTION = $(MAKE) -C $(BUILD_DIR_64)/keama DESTDIR=$(PROTO_DIR) install

install:	build $(INSTALL_64) $(PROTO_DIR)/dhcpd.leases

$(PROTO_DIR)/dhcpd.leases:	$(INSTALL_64)
	$(TOUCH) $@

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
