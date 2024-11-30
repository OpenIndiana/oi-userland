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
# Copyright (c) 2016, Aurelien Larcher. All rights reserved.
# Copyright (c) 2021, Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libcdr
COMPONENT_VERSION=	0.1.8
COMPONENT_SUMMARY=	libcdr - library for reading CorelDRAW documents
COMPONENT_PROJECT_URL=	https://wiki.documentfoundation.org/DLP/Libraries/libcdr
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:ced677c8300b29c91d3004bb1dddf0b99761bf5544991c26c2ee8f427e87193c
COMPONENT_ARCHIVE_URL=	https://dev-www.libreoffice.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	library/c++/libcdr
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      MPLv2
COMPONENT_LICENSE_FILE= COPYING.MPL

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS+= -std=c++17 -pthread

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static

COMPONENT_TEST_TRANSFORMS += '-e "s/^\# //" '

# Build dependencies
REQUIRED_PACKAGES += developer/cppunit

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
