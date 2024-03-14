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
# Copyright (c) 2015, Aurelien Larcher. All rights reserved.
#
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xcb-util-wm
COMPONENT_VERSION=	0.4.2
COMPONENT_SUMMARY=      The X protocol C-language Binding (XCB): client and window-manager helpers for EWMH and ICCCM
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://xcb.freedesktop.org/XcbUtil
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:62c34e21d06264687faea7edbf63632c9f04d55e72114aa4a57bb95e4f888a0b
COMPONENT_ARCHIVE_URL=	https://xcb.freedesktop.org/dist/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	x11/library/xcb-util-wm
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_LICENSE=      MIT

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxcb
