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
BUILD_BITS= 		64_and_32
# For now, all things built for C++11 require gcc.
COMPILER= 		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		enchant
COMPONENT_VERSION=	1.6.0
COMPONENT_PROJECT_URL=	http://www.abisource.com/projects/enchant/
COMPONENT_ARCHIVE_HASH=	\
	sha256:2fac9e7be7e9424b2c5570d8affe568db39f7572c10ed48d4e13cddf03f7097f
COMPONENT_ARCHIVE_URL=	http://www.abisource.com/downloads/enchant/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/enchant
COMPONENT_ANITYA_ID=	6601

TPNO=			9326

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

CONFIGURE_OPTIONS += --disable-static

# Force re-generate of configure since original configure is so old.
COMPONENT_PREP_ACTION += (cd $(@D); $(CONFIG_SHELL) autogen.sh --no-configure);

REQUIRED_PACKAGES += developer/build/autoconf
REQUIRED_PACKAGES += developer/build/automake
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
