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
# Copyright (c) 2020, Aurelien Larcher. All rights reserved.
#
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libfreehand
COMPONENT_VERSION=      0.1.2
COMPONENT_REVISION=     4
COMPONENT_FMRI=         library/c++/libfreehand
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=  https://wiki.documentfoundation.org/DLP/Libraries/libfreehand
COMPONENT_SUMMARY=      libfreehand - library for reading Aldus/Macromedia/Adobe FreeHand documents
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:0e422d1564a6dbf22a9af598535425271e583514c0f7ba7d9091676420de34ac
COMPONENT_ARCHIVE_URL=  http://dev-www.libreoffice.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MPLv2

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS+= -std=c++11 -pthread

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=     --without-docs

# Build dependencies
REQUIRED_PACKAGES += developer/cppunit

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
