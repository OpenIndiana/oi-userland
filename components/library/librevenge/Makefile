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
# Copyright (c) 2015, Apostolos Syropoulos. All rights reserved.
# Copyright (c) 2015-207, Aurelien Larcher. All rights reserved.
#
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         librevenge
COMPONENT_VERSION=      0.0.5
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      librevenge - base library for writing document import filters
COMPONENT_PROJECT_URL=  https://sourceforge.net/p/libwpd/wiki/librevenge/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:106d0c44bb6408b1348b9e0465666fa83b816177665a22cd017e886c1aaeeb34
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/libwpd/files/librevenge/librevenge-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/c++/librevenge
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      LGPLv2.1 MPLv2

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS += -pthread

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-werror

# Build dependencies
REQUIRED_PACKAGES += system/library/boost

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
