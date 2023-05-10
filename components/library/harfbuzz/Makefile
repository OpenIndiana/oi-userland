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
# Copyright (c) 2021-2023, Andreas Wacknitz
#

BUILD_BITS= 64_and_32
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         harfbuzz
COMPONENT_VERSION=      7.3.0
COMPONENT_FMRI=         library/c++/harfbuzz
COMPONENT_SUMMARY=      HarfBuzz - an OpenType text shaping engine. 
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.freedesktop.org/wiki/Software/HarfBuzz/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:20770789749ac9ba846df33983dbda22db836c70d9f5d050cb9aa5347094a8fb
COMPONENT_ARCHIVE_URL=  https://github.com/harfbuzz/harfbuzz/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# We want graphite2 support:
CONFIGURE_OPTIONS	 += -Dgraphite=enabled
# Creating documentation fails:
CONFIGURE_OPTIONS	 += -Ddocs=disabled
# We don't have gobject-introspection for 32-bit:
CONFIGURE_OPTIONS.32 += -Dintrospection=disabled
# Building benchmark fails:
CONFIGURE_OPTIONS.64 += -Dbenchmark=disabled

LDFLAGS += -lm

# Workaround for build failures due to pango Makefiles not passing CFLAGS or
# LDFLAGS, especially the -m32/64 flag, to g-ir-scanner
COMPONENT_BUILD_ENV += CC="$(strip $(CC))"
COMPONENT_BUILD_ENV += CFLAGS="$(strip $(CFLAGS))"
COMPONENT_BUILD_ENV += LDFLAGS="$(strip $(LDFLAGS))"

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS  = "'/Ok:|Expected Fail:|Fail:|Unexpected Pass:|Skipped:|Timeout:/'"

# Build dependencies
# Make sure the following package is synchronized with library/icu at major version changes
REQUIRED_PACKAGES += developer/icu

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/graphite2
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
