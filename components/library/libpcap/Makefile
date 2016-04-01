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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libpcap
COMPONENT_VERSION=	1.5.1
COMPONENT_PROJECT_URL=	http://www.tcpdump.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:259db4fe1e9f0b6b9c43a057ec5916dec7d0a821b00d6d6c4dff7db2445fa7e4
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)release/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libpcap

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

#
# libpcap Makefile does not use CFLAGS when building shared library
# so we require the following line to add the -m option to CC
#
CC += $(CC_BITS)

CFLAGS += "-DHAVE_CONFIG_H"

CONFIGURE_OPTIONS  +=  --disable-dbus

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:	$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
