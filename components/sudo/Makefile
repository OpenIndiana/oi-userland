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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sudo
SRC_VERSION=	1.7.4
SRC_PATCH_VERSION=	4
COMPONENT_VERSION=	$(SRC_VERSION).$(SRC_PATCH_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(SRC_VERSION)p$(SRC_PATCH_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:c873f509f80d5722989a912a42a61ad27b71453f
COMPONENT_ARCHIVE_URL=	http://www.sudo.ws/sudo/dist/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.sudo.ws/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_ENV +=	"CC=$(CC)"
CONFIGURE_ENV +=	"CFLAGS=$(CFLAGS)"
CONFIGURE_ENV +=	"CXX=$(CXX)"
CONFIGURE_ENV +=	"MAKE=$(GMAKE)"

CONFIGURE_OPTIONS +=	--with-noexec=/usr/lib/sudo_noexec.so
CONFIGURE_OPTIONS +=	--with-CC=$(CC)
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-project
CONFIGURE_OPTIONS +=	--with-timedir=/var/run/sudo

COMPONENT_BUILD_ENV +=	CC=$(CC) CXX=$(CXX)
COMPONENT_BUILD_ENV +=	"CFLAGS=$(CFLAGS)"

# For the 64-bit build, only need the 64-bit shared libraries 
COMPONENT_BUILD_TARGETS.64 = libsudo_noexec
COMPONENT_BUILD_TARGETS += $(COMPONENT_BUILD_TARGETS.$(BITS))

# This value is used in the configured Makefile for sudo,
# via the patch to Makefile.in, to install into the $(MACH64) directory
COMPONENT_INSTALL_ENV.64 +=	MACH64=$(MACH64)

# 32-bit install uses the usual target
COMPONENT_INSTALL_TARGETS.32 = install
# For 64-bit install, only install the 64-bit shared library
COMPONENT_INSTALL_TARGETS.64 = install-noexec
COMPONENT_INSTALL_TARGETS = $(COMPONENT_INSTALL_TARGETS.$(BITS))

# common targets

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
