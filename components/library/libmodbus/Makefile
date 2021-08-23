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
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmodbus
COMPONENT_VERSION=	3.1.6
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	Cross-platform library to send/receive data according to the Modbus protocol with RTU (serial) and TCP (Ethernet) communications
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d7d9fa94a16edb094e5fdf5d87ae17a0dc3f3e3d687fead81835d9572cf87c16
COMPONENT_ARCHIVE_URL=	https://libmodbus.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://libmodbus.org/
COMPONENT_LICENSE=	LGPLv2.1+
COMPONENT_LICENSE_FILE=	libmodbus.license

include $(WS_MAKE_RULES)/common.mk

# Find issues with undefined symbols in build time
LD_OPTIONS += $(LD_Z_DEFS)

COMPONENT_PREP_ACTION = ( cd $(@D); $(AUTORECONF) -if )

CONFIGURE_OPTIONS +=	--enable-static=no

COMPONENT_BUILD_ARGS +=	"LDFLAGS=$(LDFLAGS) -lsocket"
COMPONENT_BUILD_ARGS +=	"INSTALL=$(INSTALL)"
COMPONENT_BUILD_ARGS +=	"MAKE=$(GMAKE)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
