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
# Copyright 2020, Andreas Wacknitz
#
BUILD_BITS=					32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				apr
COMPONENT_VERSION=			1.7.0
COMPONENT_PROJECT_URL=		https://apr.apache.org/
COMPONENT_FMRI=				library/apr
COMPONENT_SUMMARY=			Apache Portable Runtime (APR) Shared Libraries
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_SRC= 				$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=			$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:48e9dbf45ae3fdc7b491259ffb6ccf7d63049ffacbc1c0977cced095e4c2d5a2
COMPONENT_ARCHIVE_URL=		https://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=			Apache v2.0

CONFIGURE_DEFAULT_DIRS=no

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PATCH_LEVEL=0

CFLAGS += -DSSL_EXPERIMENTAL -DSSL_ENGINE

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_PREFIX=		$(USRDIR)/apr

CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	--enable-other-child
CONFIGURE_OPTIONS +=	--enable-nonportable-atomics
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	LTFLAGS="--tag=CC --silent"
CONFIGURE_OPTIONS.32 +=	--enable-layout=OpenSolaris
CONFIGURE_OPTIONS.64 +=	--enable-layout=OpenSolaris-$(MACH64)

COMPONENT_TEST_TARGETS=	test

COMPONENT_TEST_TRANSFORMS += \
        '-e "/microseconds: [0-9]* usec/d" '  \
    '-e "/^Calling apr_socket_sendfile().../,/^apr_socket_sendfile()->*/d" ' \
    '-e "/^APR Lock Performance Test/,/make\[2\]: Leaving directory/p" ' \
    '-e "/.*/d" '

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

# Some patches need configure script recreation.
COMPONENT_PRE_CONFIGURE_ACTION += (cd $(@D); autoconf);

# 32 and 64 bits apr.h headers need to be merged to the final one.
APRH=include/apr.h
$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION += \
    diff -D __$(MACH64) $(BUILD_DIR_32)/$(APRH) \
      $(BUILD_DIR_64)/$(APRH) > $(PROTO_DIR)$(CONFIGURE_PREFIX)/$(APRH);

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION += \
    cd $(SOURCE_DIR); \
    $(GSED) 's;OUTPUT_DIRECTORY=.*;OUTPUT_DIRECTORY=$(PROTO_DIR)$(CONFIGURE_PREFIX);' \
          docs/doxygen.conf | doxygen - ;

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
