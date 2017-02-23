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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		diffstat
COMPONENT_VERSION=	1.61
COMPONENT_PROJECT_URL=	http://invisible-island.net/diffstat/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:25359e0c27183f997b36c9202583b5dc2df390c20e22a92606af4bf7856a55ee
COMPONENT_ARCHIVE_URL=	ftp://invisible-island.net/diffstat/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/diffstat
COMPONENT_ANITYA_ID=	434

TPNO=			27077

SYSTEM_TEST_TARGET= $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/common.mk

# Fix 64-bit linking done via compiler.
LDFLAGS += $(CC_BITS)

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^Checking/d" '

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_ENV =	PATH=$(@D):$(SOURCE_DIR):$(PATH)
COMPONENT_TEST_CMD =	./testing/run_test.sh
COMPONENT_TEST_ARGS =	./testing/case*.pat
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_SYSTEM_TEST_ENV =	PATH=$(USRBINDIR):$(SOURCE_DIR):$(PATH)
COMPONENT_SYSTEM_TEST_CMD =	./testing/run_test.sh
COMPONENT_SYSTEM_TEST_ARGS =	./testing/case*.pat
COMPONENT_SYSTEM_TEST_TARGETS =
