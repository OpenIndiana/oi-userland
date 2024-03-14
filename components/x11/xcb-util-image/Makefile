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
# Copyright (c) 2013-2015, Aurelien Larcher. All rights reserved.
#

BUILD_BITS = 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xcb-util-image
COMPONENT_VERSION=	0.4.1
COMPONENT_SUMMARY=      The X protocol C-language Binding (XCB): Port of XImage and XShmImage functions.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://xcb.freedesktop.org/XcbUtil
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:ccad8ee5dadb1271fd4727ad14d9bd77a64e505608766c4e98267d9aede40d3d
COMPONENT_ARCHIVE_URL=	https://xcb.freedesktop.org/dist/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	x11/library/xcb-util-image
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_LICENSE=      MIT

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/xcb-util
