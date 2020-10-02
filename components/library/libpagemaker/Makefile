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
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libpagemaker
COMPONENT_VERSION=	0.0.4
COMPONENT_REVISION=	1
COMPONENT_FMRI=     	library/c++/libpagemaker
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	https://wiki.documentfoundation.org/DLP/Libraries/libpagemaker
COMPONENT_SUMMARY=      libpagemaker - library for reading Aldus/Adobe PageMaker documents
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:66adacd705a7d19895e08eac46d1e851332adf2e736c566bef1164e7a442519d
COMPONENT_ARCHIVE_URL=	http://dev-www.libreoffice.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MPLv2

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS+= -std=c++11 -pthread

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
