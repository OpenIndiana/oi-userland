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

COMPONENT_NAME=		libmusicbrainz
COMPONENT_VERSION=	5.1.0
COMPONENT_PROJECT_URL=	https://musicbrainz.org/
COMPONENT_ARCHIVE_HASH= \
	sha256:6749259e89bbb273f3f5ad7acdffb7c47a2cf8fcaeab4c4695484cef5f4c6b46
COMPONENT_ARCHIVE_URL=	https://github.com/metabrainz/$(COMPONENT_NAME)/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/multimedia

TPNO=			24461

BUILD_STYLE= cmake

# Tests do not work on Solaris yet
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/neon
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
