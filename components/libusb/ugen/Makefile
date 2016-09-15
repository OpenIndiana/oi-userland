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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libusb-ugen
COMPONENT_VERSION=	0.1.8
IPS_COMPONENT_VERSION=	0.5.11
COMPONENT_PROJECT_URL=	http://libusb.sf.net/
COMPONENT_SRC=		src
COMPONENT_ARCHIVE_SRC=	none
COMPONENT_BUGDB=	library/libusb

BUILD_STYLE= justmake
include $(WS_MAKE_RULES)/common.mk

$(BUILD_DIR_32)/.built:	BITS=32
$(BUILD_DIR_64)/.built:	BITS=64
COMPONENT_BUILD_ARGS += BITS=$(BITS)

$(BUILD_DIR_32)/.installed:	BITS=32
$(BUILD_DIR_64)/.installed:	BITS=64
COMPONENT_INSTALL_ARGS += BITS=$(BITS)

# Do not apply the standard licence transforms for this component.
LICENSE_TRANSFORMS =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

CLEAN_PATHS +=	$(SOURCE_DIR)/.prep

# test enumerates USB devices plugged into your system

REQUIRED_PACKAGES += system/io/usb
