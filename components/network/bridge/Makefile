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

COMPONENT_NAME=		bridge
COMPONENT_VERSION=	0.1.3.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	The 'brdg' is a STREAMS module which enables briging 2 interfaces
COMPONENT_DESCRIPTION=	$(COMPONENT_SUMMARY), \
and 'brdgadm' is a configuration command to add/delete bridge interfaces. \
This program is not tested well. It might cause system panic or hang. \
DON'T install this on production system. Use this at your own risk.
COMPONENT_GIT_REV=	4b4e3ed
COMPONENT_SRC=		kaizawa-$(COMPONENT_NAME)-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4eb9d76152081284d7f1ff5c7a60116d463bffc1a0724f5ecda85592db09b283
COMPONENT_PROJECT_URL=	http://www.whiteboard.ne.jp/~admin2/tuntap/
COMPONENT_ARCHIVE_URL= 	https://codeload.github.com/kaizawa/$(COMPONENT_NAME)/legacy.tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_FMRI=		driver/network/brdg
COMPONENT_CLASSIFICATION=	Drivers/Networking
COMPONENT_LICENSE=	CDDL,BSD
COMPONENT_LICENSE_FILE=	brdg.license

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && autoreconf -fiv )

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

# Silence gcc-14
CFLAGS += -Wno-error=incompatible-pointer-types

CONFIGURE_OPTIONS += --enable-64bit

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
