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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		isc-dhcp
COMPONENT_VERSION=	4.3.3-P1
HUMAN_VERSION=		$(COMPONENT_VERSION)-S1
IPS_COMPONENT_VERSION=	4.3.3.1.1
COMPONENT_SRC_NAME=	dhcp
COMPONENT_PROJECT_URL=	http://www.isc.org/software/dhcp/
COMPONENT_ARCHIVE_URL=  \
    http://ftp.isc.org/isc/dhcp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:c11e896dffa1bfbc49462965d3f6dec45534e34068603546d9a236f2aa669921
COMPONENT_BUGDB=	service/dhcp-server

TPNO=			27530

INSTALL_TARGET=
include $(WS_MAKE_RULES)/common.mk

LINT_FLAGS +=   -I$(BUILD_DIR_32)/includes \
	-I$(BUILD_DIR_64)/includes -I$(BUILD_DIR_32)/bind/include \
	-I$(BUILD_DIR_64)/bind/include -I$(SOURCE_DIR)/includes -I.

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Some patches need configure script re-creation.
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf -vfi);

CONFIGURE_OPTIONS  +=	--sysconfdir=$(ETCDIR)/inet
CONFIGURE_OPTIONS  +=	--sbindir=$(USRLIBDIR)/inet
CONFIGURE_OPTIONS  +=	--bindir=$(USRSBINDIR)
CONFIGURE_OPTIONS  +=	--enable-use-sockets
CONFIGURE_OPTIONS  +=	--enable-ipv4-pktinfo
CONFIGURE_OPTIONS  +=	--with-pic
CONFIGURE_OPTIONS +=	--srcdir=$(BUILD_DIR_$(BITS))

CFLAGS += -g -fPIC

COMPONENT_TEST_DIR =	$(@D)

install:	build $(INSTALL_32_and_64) $(PROTO_DIR)/dhcpd.leases

$(PROTO_DIR)/dhcpd.leases:	$(INSTALL_32_and_64)
	$(TOUCH) $@

# Package dependencies
# Created by 'gmake REQUIRED_PACKAGES', manually verified.
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
