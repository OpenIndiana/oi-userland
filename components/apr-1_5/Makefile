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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apr
COMPONENT_VERSION=	1.5.0
COMPONENT_PROJECT_URL=	http://apr.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9879f02054cb22e99f605f6fdbf47f4c028af4cd4f351cf64186a7ee447f35d7
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

TPNO=			16531

CONFIGURE_DEFAULT_DIRS=no

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

# CC will be used via libtool for linking (thus need to be bitness aware).
CC+=$(CC_BITS)

CONFIGURE_PREFIX=/usr/apr/1.5

CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	--enable-other-child
CONFIGURE_OPTIONS +=	--enable-nonportable-atomics
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LTFLAGS="--tag=CC --silent"
CONFIGURE_OPTIONS.32 +=	--enable-layout=Solaris
CONFIGURE_OPTIONS.64 +=	--enable-layout=Solaris-$(MACH64)

COMPONENT_TEST_TARGETS=	test

# Some patches need configure script recreation.
COMPONENT_PREP_ACTION += (cd $(@D); autoconf);

# 32 and 64 bits apr.h headers need to be merged to the final one.
APRH=include/apr.h
$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION += \
	diff -D __$(MACH64) $(BUILD_DIR_32)/$(APRH) \
	  $(BUILD_DIR_64)/$(APRH) > $(PROTO_DIR)$(CONFIGURE_PREFIX)/$(APRH);

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION += \
	cd $(SOURCE_DIR); \
	sed 's;OUTPUT_DIRECTORY=.*;OUTPUT_DIRECTORY=$(PROTO_DIR)$(CONFIGURE_PREFIX);' \
          docs/doxygen.conf | doxygen - ;

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
