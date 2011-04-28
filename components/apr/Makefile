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

COMPONENT_NAME=		apr
COMPONENT_VERSION=	1.3.9
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:3ad0099ee9fb684e118590bf0acf937639e00611
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

CONFIGURE_PREFIX=/usr/apr/1.3

CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	--enable-other-child
CONFIGURE_OPTIONS +=	--enable-nonportable-atomics
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS) -DSSL_EXPERIMENTAL -DSSL_ENGINE"
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
	  $(BUILD_DIR_64)/$(APRH) > $(PROTO_DIR)/$(APR_PREFIX)/$(APRH); true

# Documentation is generated in and directly packaged from 32 bit build
# directory using doxygen.
PKG_PROTO_DIRS += $(BUILD_DIR_32)/docs/dox/html

docs: $(BUILD_DIR_32)/.built
	cd $(BUILD_DIR_32); doxygen docs/doxygen.conf

build: $(BUILD_32_and_64) docs

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
