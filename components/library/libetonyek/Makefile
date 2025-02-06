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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libetonyek
COMPONENT_VERSION=	0.1.12
COMPONENT_SUMMARY=      libetonyek - library for reading Apple iWork documents
COMPONENT_PROJECT_URL=	https://wiki.documentfoundation.org/DLP/Libraries/libetonyek
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:b9fa82fbeb8cb7a701101060e4f3e1e4ef7c38f574b2859d3ecbe43604c21f83
COMPONENT_ARCHIVE_URL=	https://dev-www.libreoffice.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	library/c++/libetonyek
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MPLv2
COMPONENT_LICENSE_FILE= COPYING

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS += -std=c++17 -pthread

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-mdds=2.1

unexport SHELLOPTS

# Build dependencies
REQUIRED_PACKAGES += library/c++/mdds
REQUIRED_PACKAGES += library/math/glm

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/liblangtag
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
