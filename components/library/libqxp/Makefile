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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libqxp
COMPONENT_VERSION=	0.0.3
COMPONENT_SUMMARY=	libqxp - library for reading QuarkXPress documents
COMPONENT_PROJECT_URL=	https://wiki.documentfoundation.org/DLP/Libraries/libqxp
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:4687a9cc96c32d7406e5072c4da150fca696c563e5cde62b024f82fa53d32332
COMPONENT_ARCHIVE_URL=  https://dev-www.libreoffice.org/src/libqxp/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	library/c++/libqxp
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	MPL-2.0
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS += -std=c++17 -pthread

CONFIGURE_OPTIONS += --without-docs
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
