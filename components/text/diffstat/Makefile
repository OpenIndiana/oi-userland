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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
#
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		diffstat
COMPONENT_VERSION=	1.62
COMPONENT_FMRI=	text/diffstat
COMPONENT_SUMMARY=	A utility which provides statistics based on the output of diff
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_PROJECT_URL=	http://invisible-island.net/diffstat/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
  sha256:7f09183644ed77a156b15346bbad4e89c93543e140add9dab18747e30522591f
COMPONENT_ARCHIVE_URL= \
  https://invisible-mirror.net/archives/diffstat/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

CC += $(CC_BITS)

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_ENV =	PATH=$(@D):$(SOURCE_DIR):$(PATH)
COMPONENT_TEST_CMD =	./testing/run_test.sh
COMPONENT_TEST_ARGS =	./testing/case*.pat
COMPONENT_TEST_TARGETS =

COMPONENT_TEST_TRANSFORMS= \
	'-e "/Checking/d"'

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
