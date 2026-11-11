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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         librevenge
COMPONENT_VERSION=	0.0.6
COMPONENT_SUMMARY=      librevenge - base library for writing document import filters
COMPONENT_PROJECT_URL=  https://sourceforge.net/p/libwpd/wiki/librevenge/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:19eacf5ce55d7fe6a990a45142589cdf7da0c7b68701797f133482cb44f189fa
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/libwpd/files/librevenge/librevenge-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/c++/librevenge
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      LGPLv2.1 MPLv2

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf -- '--- COPYING.LGPL ----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LGPL ; \
		printf '\n\n--- COPYING.MPL -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.MPL \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# Fix threading detection issue introduced with boost 1.64
CXXFLAGS += -pthread

CONFIGURE_OPTIONS += --without-docs
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
