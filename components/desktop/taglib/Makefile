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
BUILD_BITS= 32_and_64
# For now, all things built for C++11 require gcc.
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		taglib
COMPONENT_VERSION=	1.9.1
COMPONENT_PROJECT_URL=	https://taglib.github.io/
COMPONENT_ARCHIVE_HASH= \
	sha256:72d371cd1419a87ae200447a53bff2be219283071e80fd12337928cc967dc71a
COMPONENT_ARCHIVE_URL=	https://taglib.github.io/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/taglib

TPNO=			27551

PATCH_LEVEL= 0

BUILD_STYLE= cmake

ASLR_MODE = $(ASLR_ENABLE)

# disable tests for now - 23214794
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
