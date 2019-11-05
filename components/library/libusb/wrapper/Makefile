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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libusb-wrapper
COMPONENT_VERSION=	0.1.8
COMPONENT_REVISION=	1
IPS_COMPONENT_VERSION=	0.5.11
COMPONENT_PROJECT_URL=	http://libusb.sf.net/
COMPONENT_SRC=		src
COMPONENT_BUGDB=	library/libusb

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

$(BUILD_DIR_32)/.built: BITS=32
$(BUILD_DIR_64)/.built: BITS=64
COMPONENT_BUILD_ARGS += BITS=$(BITS)

$(BUILD_DIR_32)/.installed:     BITS=32
$(BUILD_DIR_64)/.installed:     BITS=64
COMPONENT_INSTALL_ARGS += BITS=$(BITS)

# common targets
$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

$(BUILD_DIR)/libusb-64.pc:	src/libusb-64.pc $(BUILD_DIR) $(MAKEFILE_PREREQ)
	/bin/sed -e "s#MACH64#$(MACH64)#g" <$< >$@

download:

clobber:	clean
	$(RM) $(SOURCE_DIR)/.prep

prep:	$(SOURCE_DIR)/.prep

build:		$(BUILD_32_and_64) $(BUILD_DIR)/libusb-64.pc

install:	$(INSTALL_32_and_64)

# enumerates USB devices plugged into your system
test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
