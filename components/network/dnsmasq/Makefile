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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, 2020, Andreas Wacknitz
#

BUILD_BITS= 64
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dnsmasq
COMPONENT_VERSION=	2.89
COMPONENT_SUMMARY=	dnsmasq is a DNS forwarder for NAT firewalls
COMPONENT_DESCRIPTION=	dnsmasq(8) is a lightweight DNS, TFTP, PXE, router advertisement and DHCP server. \
						It is intended to provide coupled DNS and DHCP service to a LAN.
COMPONENT_PROJECT_URL=	https://www.thekelleys.org.uk
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8651373d000cae23776256e83dcaa6723dee72c06a39362700344e0c12c4e7e4
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		service/network/dnsmasq
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2, GPLv3

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# i18n component requires GNU xgettext
PATH= $(PATH.gnu)

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

CPPFLAGS += $(CPP_XPG6MODE)
CPPFLAGS += $(CPP_LARGEFILES)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += PREFIX="/usr"
COMPONENT_BUILD_ARGS += LOCALEDIR="/usr/share/locale"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS) -m$(BITS)"
COMPONENT_BUILD_TARGETS = "all-i18n"
COMPONENT_INSTALL_ENV += CC="$(CC)"
COMPONENT_INSTALL_ARGS += CC="$(CC)"
COMPONENT_INSTALL_ARGS += PREFIX="/usr"
COMPONENT_INSTALL_ARGS += BINDIR="$(USRLIBDIR)/inet"
COMPONENT_INSTALL_TARGETS = "install-i18n"

# Manually added build dependencies
REQUIRED_PACKAGES += library/libidn

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
