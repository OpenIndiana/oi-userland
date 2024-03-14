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
# Copyright (c) 2023 Klaus Ziegler
#

USE_OPENSSL11= no
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcltls
COMPONENT_MAJOR_VERSION= 1.6
COMPONENT_MINOR_VERSION= 7
COMPONENT_REVISION=	3
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_SUMMARY=	TCL bindings for OpenSSL
COMPONENT_PROJECT_URL=	https://core.tcl-lang.org/tcltls
COMPONENT_SRC_NAME=	tls
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:5119de3e5470359b97a8a00d861c9c48433571ee0167af0a952de66c99d3a3b8
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/uv/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_FMRI=		runtime/tcl-8/tcl-openssl
COMPONENT_LICENSE=	BSD-like

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += COMPONENT_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

CONFIGURE_OPTIONS += --with-tclinclude=/usr/include
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --with-tcl="$(COMPONENT_DIR)/../tcl/build/$(MACH$(BITS))"
CONFIGURE_OPTIONS += --enable-64bit
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS += CPPFLAGS="-I$(OPENSSL_PREFIX)/include -I/usr/include/odbc"
ifeq ($(strip $(MACH)),sparc)
CONFIGURE_OPTIONS += --enable-64bit-vis
endif

COMPONENT_TEST_TARGETS= test
COMPONENT_TEST_TRANSFORMS= \
	'-n' \
	'-e "/Total/p"' \
	'-e "/Sourced/p"' \
	'-e "/failing/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
