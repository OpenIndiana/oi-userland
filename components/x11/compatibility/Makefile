#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           x11-compatibility
COMPONENT_VERSION=        $(PKG_OS_VERSION)
COMPONENT_REVISION=       2
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_LICENSE=        Oracle

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_PROTO_DIRS=$(MANGLED_DIR)

PKG_MACROS+= OSPKGVERS="$(IPS_COMPONENT_VERSION),$(BUILD_VERSION)"

build: 

install: 

test: $(NO_TESTS)

