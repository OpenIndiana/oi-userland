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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libusb
COMPONENT_VERSION=	1.0.23
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:db11c06e958a82dac52cf3c65cb4dd2c3f339c8a988665110e0d24d19312ad8d
COMPONENT_ARCHIVE_URL=  https://github.com/libusb/libusb/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://libusb.info/
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

COMPONENT_PREP_ACTION = ( cd $(@D); $(AUTORECONF) -if )

CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS +=	--enable-log
CONFIGURE_OPTIONS +=	--enable-tests-build

COMPONENT_BUILD_ARGS +=	"LDFLAGS=$(LDFLAGS) -lnvpair"
COMPONENT_BUILD_ARGS +=	"INSTALL=$(INSTALL)"
COMPONENT_BUILD_ARGS +=	"MAKE=$(GMAKE)"

# Test target just runs the 'stress' binary; requires Global Zone
COMPONENT_TEST_TARGETS=
COMPONENT_TEST_ENV_CMD=
COMPONENT_TEST_DIR= $(BUILD_DIR)/$(MACH$(BITS))/tests/.libs
COMPONENT_TEST_CMD= ./stress

# Build dependencies
REQUIRED_PACKAGES += system/header/header-usb
REQUIRED_PACKAGES += system/header/header-ugen
