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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pigz
COMPONENT_VERSION=	2.3.3
COMPONENT_PROJECT_URL=	http://zlib.net/pigz/
COMPONENT_ARCHIVE_HASH=	\
    sha256:4e8b67b432ce7907575a549f3e1cac4709781ba0f6b48afea9f59369846b509c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	3642

TPNO=			31875

BUILD_STYLE= justmake
INSTALL_TARGET= build
SYSTEM_TEST_TARGET= $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS += $(BUILD_DIR_64)

studio_C99MODE=	$(studio_C99_ENABLE) 

CC += $(CC_BITS)
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS) -DHAVE_PTHREAD_SETNAME_NP"
COMPONENT_SYSTEM_TEST_TARGETS=	test
COMPONENT_SYSTEM_TEST_ENV=	TARGETDIR=$(USRBINDIR)
COMPONENT_TEST_TARGETS=	test
# Ignore these warnings that can come in random order.
COMPONENT_TEST_TRANSFORMS += \
    '-e "/skipping:/d" ' \
    '-e "/Entering/d"' \
    '-e "/Leaving/d"'

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/math
