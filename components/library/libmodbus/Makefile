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
# Copyright (c) 2021, Jim Klimov
# Copyright (c) 2022, Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmodbus
COMPONENT_VERSION=	3.1.10
COMPONENT_SUMMARY=	Cross-platform library to send/receive data according to the Modbus protocol with RTU (serial) and TCP (Ethernet) communications
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:899be4e25ab7fe5799d43f9567510d6f063d2e8f56136dd726b6fd976f9b2253
COMPONENT_ARCHIVE_URL=	https://github.com/stephane/libmodbus/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://libmodbus.org/
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	LGPLv2.1+
COMPONENT_LICENSE_FILE=	COPYING.LESSER

include $(WS_MAKE_RULES)/common.mk

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

COMPONENT_PREP_ACTION = ( cd $(@D); $(AUTORECONF) -if )

CONFIGURE_OPTIONS +=	--enable-static=no

COMPONENT_BUILD_ARGS +=	"LDFLAGS=$(LDFLAGS) -lsocket"
COMPONENT_BUILD_ARGS +=	"INSTALL=$(INSTALL)"
COMPONENT_BUILD_ARGS +=	"MAKE=$(GMAKE)"

# This is needed to make the tests successful:
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
