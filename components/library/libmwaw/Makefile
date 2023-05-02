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
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmwaw
COMPONENT_VERSION=	0.3.22
COMPONENT_FMRI=     library/c++/libmwaw
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_PROJECT_URL=	https://wiki.documentfoundation.org/DLP/Libraries/libmwaw
COMPONENT_SUMMARY=      A library for reading various old mac text documents
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:a1a39ffcea3ff2a7a7aae0c23877ddf4918b554bf82b0de5d7ce8e7f61ea8e32
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/libmwaw/files/libmwaw/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=      LGPLv2, MPLv2

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS += -std=c++11 -pthread

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
