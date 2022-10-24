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
# Copyright 2013, Adam Stevko. All rights reserved.
# Copyright 2015-2016, Jim Klimov
# Copyright 2022, Till Wegmueller
#

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tuntap
COMPONENT_VERSION=	1.3.3
COMPONENT_LICENSE=	GPLv2
COMPONENT_GIT_REV=	10850b5
COMPONENT_SRC=		kaizawa-$(COMPONENT_NAME)-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:83d095060905196826ed7fa133b24b6ae62b9ecbc219383261eeaf890c243179
COMPONENT_PROJECT_URL=	http://www.whiteboard.ne.jp/~admin2/tuntap/
COMPONENT_ARCHIVE_URL= 	https://codeload.github.com/kaizawa/$(COMPONENT_NAME)/legacy.tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_CLASSIFICATION=	Drivers/Networking
COMPONENT_DESCRIPTION=	tuntap is a Virtual Point-to-Point network device: \
a TAP driver for OpenIndiana that can be used for \
OpenVPN, OpenConnect, wireguard (tailscale) and vpnc. The code is based on the \
Universal TUN/TAP driver. Some changes were made and code added \
for supporting Ethernet tunneling feature, since the Universal \
TUN/TAP driver for Solaris only supports IP tunneling known as TUN.

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) && autoreconf -fiv)

COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)

CFLAGS +=	$(CPP_LARGEFILES)
# Ensure that the standard function prologue remains at the very start of a
# function, so DTrace fbt will instrument the right place.
CFLAGS += -fno-shrink-wrap

# Build the kernel module with retpolines and other settings that are used in
# illumos-gate
CFLAGS += -ffreestanding 
CFLAGS += -mcmodel=kernel
CFLAGS += -mno-mmx 
CFLAGS += -mno-sse 
CFLAGS += -mno-red-zone
CFLAGS += -mindirect-branch=thunk-extern
CFLAGS += -mindirect-branch-register
CFLAGS += -msave-args
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS.32 +=  --disable-64bit
CONFIGURE_OPTIONS.64 +=  --enable-64bit

# Auto-generated dependencies
