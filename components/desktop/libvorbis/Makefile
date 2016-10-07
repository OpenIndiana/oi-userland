#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 		32_and_64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvorbis
COMPONENT_VERSION=	1.3.3
COMPONENT_PROJECT_URL=	http://downloads.xiph.org/releases/vorbis/
COMPONENT_ARCHIVE_HASH= \
	sha256:6d747efe7ac4ad249bf711527882cef79fb61d9194c45b5ca5498aa60f290762
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/multimedia

TPNO=			9575

# gmake check works and all test pass but because of hard-coded paths
# check with results-all.master fails
TEST_TARGET = $(SKIP_TEST)

# ogg-vorbis is not unlockable in S11 gnome-incorporation
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

# Replace the following with REQUIRED_PACKAGES += codec/libogg when 
# the build server is updated
# The dependency isn't installed, so add it manually since pkgdepend
# can't resolve them yet: 15708323
DEPENDED += $(WS_TOP)/components/desktop/libogg/build/manifest-$(MACH)-libogg.depend
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../libogg/Makefile)

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += system/library/math
