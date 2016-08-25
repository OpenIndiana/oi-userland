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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
COMPILER= gcc
# Prefer 32-bit as only "binary" delivered is a script with embedded paths.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cppunit
COMPONENT_VERSION=	1.13.2
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/Software/cppunit/
COMPONENT_ARCHIVE_HASH=	\
    sha256:3f47d246e3346f2ba4d7c9e882db3ad9ebd3fcbd2e8b732f946e0e3eeb9f429f
COMPONENT_ARCHIVE_URL=	http://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE)

TPNO=			20676

# Needs older version of libpng, no longer available in evaluation builds.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk


export PATH=$(GCC_ROOT)/bin:$(GNUBIN):$(USRBINDIR)

CONFIGURE_OPTIONS  +=	--disable-static

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
