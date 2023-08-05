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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright 2022, Daniel Chan
# Copyright 2023, Niklas Poslovski

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         openexr
COMPONENT_VERSION=      3.1.10
COMPONENT_SUMMARY=      OpenEXR header files and libraries used to read and write OpenEXR images
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.openexr.com/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:6e0fd3f0eb1cb907bd3593830ea2b3431b85f22a6f18f99f8cfa099fec70067d
COMPONENT_ARCHIVE_URL=  https://github.com/AcademySoftwareFoundation/openexr/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/openexr
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= LICENSE.md

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=None
CMAKE_OPTIONS += -DOPENEXR_FORCE_INTERNAL_IMATH=OFF
CMAKE_OPTIONS += -DOPENEXR_FORCE_INTERNAL_ZLIB=OFF
CMAKE_OPTIONS += -DOPENEXR_USE_DEFAULT_VISIBILITY=OFF
CMAKE_OPTIONS += -DCMAKE_INSTALL_BINDIR=bin/$(MACH64)

COMPONENT_TEST_TRANSFORMS= \
	' -e "s/[0-9]*\.[0-9]* sec/X.XX sec/" ' \
	'-n ' \
    '-e "/Passed/p" ' \
    '-e "/Failed/p" ' \
    '-e "/Skipped/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/imath
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
