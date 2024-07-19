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
# Copyright 2016 Jim Klimov
# Copyright 2020 Michal Nowak
# Copyright 2022 Niklas Poslovski
# Copyright 2024 Stephan Althaus
#

USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openvpn
COMPONENT_VERSION=	2.6.12
COMPONENT_SUMMARY=	OpenVPN is a full-featured open source SSL VPN solution
COMPONENT_PROJECT_URL=	https://openvpn.net
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1c610fddeb686e34f1367c347e027e418e07523a10f4d8ce4a2c2af2f61a1929
COMPONENT_ARCHIVE_URL=	https://build.openvpn.net/downloads/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		network/openvpn
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += GREP=/usr/gnu/bin/grep
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)/$(USRSHAREDOCDIR)/openvpn/sample/ ; \
	$(CP) -a $(SOURCE_DIR)/sample/sample-{config-files,keys,scripts} $(PROTO_DIR)/$(USRSHAREDOCDIR)/openvpn/sample/ ;

COMPONENT_TEST_TRANSFORMS += \
	'-e "/test was not run/p"' \
	'-e "/cannot find/p"'

# Build dependencies
REQUIRED_PACKAGES += driver/network/header-tun

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += system/library
