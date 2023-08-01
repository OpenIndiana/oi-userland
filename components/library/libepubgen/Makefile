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

COMPONENT_NAME=         libepubgen
COMPONENT_VERSION=      0.1.1
COMPONENT_REVISION=     2
COMPONENT_FMRI=         library/c++/libepubgen
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=  https://sourceforge.net/projects/libepubgen/
COMPONENT_SUMMARY=      libepubgen - EPUB generator for librevenge
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:03e084b994cbeffc8c3dd13303b2cb805f44d8f2c3b79f7690d7e3fc7f6215ad
COMPONENT_ARCHIVE_URL=  \
	http://sourceforge.net/projects/libepubgen/files/libepubgen-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MPLv2

include $(WS_MAKE_RULES)/common.mk

# Fix threading detection issue with boost 1.64
CXXFLAGS+= -pthread

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--without-docs

unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

# Build dependencies
REQUIRED_PACKAGES += developer/cppunit
REQUIRED_PACKAGES += system/library/boost

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
