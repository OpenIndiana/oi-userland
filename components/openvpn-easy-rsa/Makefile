#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Adam Stevko. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		easy-rsa
COMPONENT_VERSION=	2.2.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)_master
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d23ddc3a764b40d03ada76f387c92ae4dcf4f5266da54c2bae130325b05eebe2
COMPONENT_FMRI=		network/openvpn/easy-rsa
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	easy-rsa.license
COMPONENT_SUMMARY=	Simple shell based CA utility
COMPONENT_PROJECT_URL=	https://github.com/OpenVPN/easy-rsa	
COMPONENT_ARCHIVE_URL=	http://swupdate.openvpn.net/community/releases/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
