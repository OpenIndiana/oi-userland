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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
#

# Prefer 32-bit over 64-bit as apr has its own custom package layout.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apr
COMPONENT_VERSION=	1.5.2
COMPONENT_PROJECT_URL=	http://apr.apache.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:1af06e1720a58851d90694a984af18355b65bb0d047be03ec7d659c746d6dbdb
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache
COMPONENT_ANITYA_ID=	95

TPNO=			27510

CONFIGURE_DEFAULT_DIRS=no
include $(WS_MAKE_RULES)/common.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

PATCH_LEVEL=0

CONFIGURE_PREFIX=$(USRDIR)/apr/1.5

CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	--enable-other-child
CONFIGURE_OPTIONS +=	--enable-nonportable-atomics
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	LTFLAGS="--tag=CC --silent"
CONFIGURE_OPTIONS.32 +=	--enable-layout=Solaris
CONFIGURE_OPTIONS.64 +=	--enable-layout=Solaris-$(MACH64)

COMPONENT_TEST_TARGETS=	test

COMPONENT_TEST_TRANSFORMS += \
        '-e "/microseconds: [0-9]* usec/d" '  \
	'-e "/^APR Lock Performance Test/,/make\[2\]: Leaving directory/p" ' \
	'-e "/.*/d" '

# Some patches need configure script recreation; autoreconf is not used here as
# it will overwrite the patch to the libtool scripts.
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

REQUIRED_PACKAGES += database/mysql-55
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
