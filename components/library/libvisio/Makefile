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
# Copyright (c) 2017-2020, Aurelien Larcher. All rights reserved.
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libvisio
COMPONENT_VERSION=      0.1.7
COMPONENT_REVISION=		3
COMPONENT_SUMMARY=      libvisio - library for reading Microsoft Visio documents
COMPONENT_PROJECT_URL=  https://wiki.documentfoundation.org/DLP/Libraries/libvisio
COMPONENT_SRC=    $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:8faf8df870cb27b09a787a1959d6c646faa44d0d8ab151883df408b7166bea4c
COMPONENT_ARCHIVE_URL=  https://dev-www.libreoffice.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/c++/libvisio
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MPLv2
COMPONENT_LICENSE_FILE= COPYING.MPL

include $(WS_MAKE_RULES)/common.mk

# Fix threading detection issue with boost 1.64
CXXFLAGS += -std=c++11 -pthread

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
