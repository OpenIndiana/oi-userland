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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openvpn
COMPONENT_VERSION=	2.3.12
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:13b963414e2430215981868c77b9795d93653ee535a2d73576f7bb2c28200abc
COMPONENT_PROJECT_URL=	http://openvpn.net
COMPONENT_ARCHIVE_URL=	http://swupdate.openvpn.org/community/releases/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATCH_LEVEL = 0

CPPFLAGS +=	-I$(WS_TOP)/components/tuntap/build/prototype/$(MACH)/usr/include
CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += GREP=/usr/gnu/bin/grep
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-password-save

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += driver/network/header-tun
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
