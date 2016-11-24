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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tunctl
COMPONENT_GIT_DATE=	20141214
COMPONENT_GIT_REV=	e83516b
COMPONENT_VERSION=	0.1.1.$(COMPONENT_GIT_DATE)
COMPONENT_LICENSE=	GPLv2+
COMPONENT_FMRI=		driver/network/$(COMPONENT_NAME)
COMPONENT_SRC=		kaizawa-$(COMPONENT_NAME)-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6df8837e21844ab3f0f50cf9f9c7142cbeebc8bda898b566eedb19d38b88731a
COMPONENT_PROJECT_URL=	http://www.whiteboard.ne.jp/~admin2/tuntap/
COMPONENT_ARCHIVE_URL= 	https://codeload.github.com/kaizawa/$(COMPONENT_NAME)/legacy.tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_CLASSIFICATION=	Drivers/Networking
COMPONENT_SUMMARY=	The tunctl command enables administrators to preconfigure a TUN/TAP device and delete a stalled one

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# The sources include a copy of the header. As of 2016, they are identical
# to those that come with tuntap drivers - and future-wise, they should match.
COMPONENT_PREP_ACTION = \
        (cd $(@D) && rm -f if_tun.h && autoreconf -fiv)
REQUIRED_PACKAGES += driver/network/header-tun

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
