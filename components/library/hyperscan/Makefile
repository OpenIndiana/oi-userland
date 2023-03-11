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
# Copyright (c) 2023, Friedrich Kink
#
BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hyperscan
COMPONENT_VERSION=	5.4.1
COMPONENT_SUMMARY=	Hyperscan is a high-performance multiple regex matching library.
COMPONENT_PROJECT_URL=  https://www.hyperscan.io/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:6798202350ecab5ebe5063fbbb6966c33d43197b39ce7ddfbca2e61ac5ecb54a
COMPONENT_ARCHIVE_URL=  https://github.com/intel/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_FMRI=		library/hyperscan
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# turn on largefile support
CFLAGS += $(CPP_LARGEFILES)

# to avoid to modern CPU's when build automatically on newer hardware
CMAKE_OPTIONS+= -DCMAKE_C_FLAGS="-march=corei7"
CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DFAT_RUNTIME=OFF
CMAKE_OPTIONS+= -DBUILD_SHARED_LIBS=ON

TEST_TARGET=       $(NO_TESTS)

# manually added
REQUIRED_PACKAGES += developer/ragel

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
