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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			unrar
COMPONENT_VERSION=		6.2.7
COMPONENT_SRC=			$(COMPONENT_NAME)
COMPONENT_SUMMARY=		Rar archives extractor utility
COMPONENT_PROJECT_URL=	https://www.rarlabs.com/rar_add.htm
COMPONENT_ARCHIVE=		$(COMPONENT_NAME)src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f071169f3f20a564f9cf1c8976c64e72de3b9cdbcccaa43a0c66472eb737aa01
COMPONENT_ARCHIVE_URL=	https://www.rarlab.com/rar/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			archiver/unrar
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE= 		UnRAR

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

PKG_PROTO_DIRS = $(MANGLED_DIR)
PKG_PROTO_DIRS += $(BUILD_DIR_64)
PKG_PROTO_DIRS += $(COMPONENT_DIR)

# Needed by .../unrar/os.hpp to correctly define platform endianness.
CXXFLAGS.i386 = -DLITTLE_ENDIAN
CXXFLAGS.sparc = -DBIG_ENDIAN
CXXFLAGS += $(CXXFLAGS.$(MACH))
COMPONENT_BUILD_ENV += CXX="$(CXX)"
COMPONENT_BUILD_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV += DEFINES="$(CPP_LARGEFILES)"

COMPONENT_BUILD_ARGS += STRIP="/bin/true"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
