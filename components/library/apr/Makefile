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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		apr
COMPONENT_VERSION=	1.5.2
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://apr.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1af06e1720a58851d90694a984af18355b65bb0d047be03ec7d659c746d6dbdb
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

CFLAGS += -DSSL_EXPERIMENTAL -DSSL_ENGINE

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_PREFIX=/usr/apr

CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	--enable-other-child
CONFIGURE_OPTIONS +=	--enable-nonportable-atomics
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	LTFLAGS="--tag=CC --silent"
CONFIGURE_OPTIONS.32 +=	--enable-layout=OpenSolaris
CONFIGURE_OPTIONS.64 +=	--enable-layout=OpenSolaris-$(MACH64)
CONFIGURE_OPTIONS.32 +=	--with-installbuilddir=$(CONFIGURE_PREFIX)/build
CONFIGURE_OPTIONS.64 +=	--with-installbuilddir=$(CONFIGURE_PREFIX)/build/$(MACH64)

COMPONENT_TEST_TARGETS=	test

# We need this to keep doxygen happy (for include/ and docs/ contents).
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

# Some patches need configure script recreation.
COMPONENT_PRE_CONFIGURE_ACTION += (cd $(@D); autoconf);

# 32 and 64 bits apr.h headers need to be merged to the final one.
APRH=include/apr.h
$(BUILD_DIR_64)/.installed: COMPONENT_POST_INSTALL_ACTION = \
	/usr/bin/diff -D __$(MACH64) $(BUILD_DIR_32)/$(APRH) \
	  $(BUILD_DIR_64)/$(APRH) > $(PROTO_DIR)/$(CONFIGURE_PREFIX)/$(APRH); \
	$(GSED) -i -e '/^CFLAGS=""/s:CFLAGS="":CFLAGS="-m64":' $(PROTO_DIR)$(CONFIGURE_PREFIX)/bin/$(MACH64)/apr-1-config ;  true

# Documentation is generated in and directly packaged from 32 bit build
# directory using doxygen.
PKG_PROTO_DIRS += $(BUILD_DIR_32)/docs/dox/html
PKG_PROTO_DIRS += $(BUILD_DIR_32)/docs/dox/html/search

docs: $(BUILD_DIR_32)/.built
	cd $(BUILD_DIR_32); doxygen docs/doxygen.conf

build: $(BUILD_32_and_64) docs

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
