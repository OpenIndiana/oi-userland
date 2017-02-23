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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rdesktop
COMPONENT_VERSION=	1.6.0
COMPONENT_PROJECT_URL=	http://www.rdesktop.org/
COMPONENT_ARCHIVE_HASH= \
	sha256:8430390d50be29f257d575a70abe38805916dc1897b18e5a244adb72c978d4e0
COMPONENT_ARCHIVE_URL=	https://github.com/rdesktop/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	gnome/remote-desktop
COMPONENT_ANITYA_ID=	4172

TPNO=			26597

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# rdesktop-1.6.0 tarball includes configure.ac but not configure, so we make it
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv)
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --with-ipv6
CONFIGURE_OPTIONS += --with-openssl=/usr

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += x11/library/libx11
