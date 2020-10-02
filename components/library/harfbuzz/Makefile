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

#
# Copyright (c) 2015-2018, Aurelien Larcher. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2020, Andreas Wacknitz
#

BUILD_BITS=				32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         harfbuzz
COMPONENT_VERSION=      2.7.2
COMPONENT_FMRI=         library/c++/harfbuzz
COMPONENT_SUMMARY=      HarfBuzz - an OpenType text shaping engine. 
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.freedesktop.org/wiki/Software/HarfBuzz/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b8c048d7c2964a12f2c80deb6634dfc836b603dd12bf0d0a3df1627698e220ce
COMPONENT_ARCHIVE_URL=	\
	https://github.com/harfbuzz/harfbuzz/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--with-graphite2=yes
CONFIGURE_OPTIONS+=	--with-freetype=yes

LDFLAGS += -lm

unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += $(CONFIGURE_TEST_TRANSFORMS)

# Build dependencies
# Make sure the following package is synchronized with library/icu at major version changes
REQUIRED_PACKAGES += developer/icu

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/graphite2
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
