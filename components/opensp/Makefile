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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
COMPILER= gcc
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		opensp
COMPONENT_VERSION=	1.5.1
COMPONENT_PROJECT_URL=	http://openjade.sourceforge.net/
COMPONENT_SRC=		OpenSP-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:3f0649840dc3d6ec432e3c8d933b178208f3feccb6db111d22c8995ad07c736b
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/openjade/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13231

TPNO=			9621

include $(WS_MAKE_RULES)/common.mk

# Needed to find the man pages at install time.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=	--bindir=/usr/bin
CONFIGURE_OPTIONS +=	--disable-http
CONFIGURE_OPTIONS +=	--disable-nls
CONFIGURE_OPTIONS +=	--enable-default-catalog="CATALOG:/etc/sgml/catalog:/usr/share/sgml/CATALOG"
ifeq ($(OS_VERSION),5.11)
EXTRA_LIBRARIES =     -lsocket -lnsl
endif
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS) $(EXTRA_LIBRARIES)"

# 21786575 for gmake test failures
COMPONENT_TEST_DIR =	$(BUILD_DIR)/$(MACH$(BITS))/tests 
COMPONENT_TEST_ARGS = 	-k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
	'-e "/result_count/d" ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
