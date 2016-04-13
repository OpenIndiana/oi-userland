#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2015, Aurelien Larcher. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bullet
COMPONENT_VERSION=	2.83.5
COMPONENT_FMRI=     	library/bullet
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		bullet3-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://bulletphysics.org/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:df6d58898d3d3bf117854dd64467dbd09625e048624c797649b46bf1c595b152
COMPONENT_ARCHIVE_URL=	https://github.com/bulletphysics/bullet3/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=      BSD3c
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=      Bullet Physics Library

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/cmake.mk
include $(WS_TOP)/make-rules/ips.mk

LIB_SUFFIX32=
LIB_SUFFIX64=$(MACH64)

CMAKE_OPTIONS+=	-DBUILD_SHARED_LIBS=ON 
CMAKE_OPTIONS+=	-DBUILD_EXTRAS=ON
CMAKE_OPTIONS+=	-DBUILD_BULLET2_DEMOS=OFF
CMAKE_OPTIONS+=	-DBUILD_OPENGL3_DEMOS=OFF
CMAKE_OPTIONS+=	-DBUILD_CPU_DEMOS=OFF
CMAKE_OPTIONS+=	-DINSTALL_LIBS=ON 
CMAKE_OPTIONS+=	-DINSTALL_EXTRA_LIBS=ON
CMAKE_OPTIONS+=	-DCMAKE_BUILD_TYPE=Release 
CMAKE_OPTIONS+=	-DLIB_SUFFIX=/$(LIB_SUFFIX$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =    $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk

