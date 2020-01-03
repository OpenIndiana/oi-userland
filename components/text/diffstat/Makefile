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
# Copyright (c) 2020, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		diffstat
COMPONENT_VERSION=	1.63
COMPONENT_FMRI=		text/diffstat
COMPONENT_SUMMARY=	A utility which provides statistics based on the output of diff
COMPONENT_CLASSIFICATION= System/Text Tools
COMPONENT_PROJECT_URL=	http://invisible-island.net/diffstat/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
	sha256:7eddd53401b99b90bac3f7ebf23dd583d7d99c6106e67a4f1161b7a20110dc6f
COMPONENT_ARCHIVE_URL= \
	https://invisible-mirror.net/archives/diffstat/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

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

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
