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
# Copyright (c) 2026 Klaus Ziegler
#

USE_PARALLEL_BUILD = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcltls
COMPONENT_VERSION=	2.0
COMPONENT_SUMMARY=	TCL bindings for OpenSSL
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-20260121024900-5d3e3c3bf8
COMPONENT_PROJECT_URL=	https://core.tcl-lang.org/tcltls
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f1fa46067984c4096976f04f131fdea54c07ba45ce2b03a0697a0ea801e3a23a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/uv/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_FMRI=		runtime/tcl-8/tcl-openssl
COMPONENT_LICENSE=	BSD-like

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += COMPONENT_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

CONFIGURE_OPTIONS += --with-tclinclude=/usr/include
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --enable-64bit
CONFIGURE_OPTIONS += --with-openssl-dir=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS += CPPFLAGS="-I$(OPENSSL_PREFIX)/include -I/usr/include/odbc"
ifeq ($(strip $(MACH)),sparc)
CONFIGURE_OPTIONS += --enable-64bit-vis
endif

COMPONENT_TEST_TARGETS= test
COMPONENT_TEST_TRANSFORMS= \
	'-n' \
	'-e "/Total/p"' \
	'-e "/Sourced/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
