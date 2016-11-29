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

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdg-utils
COMPONENT_VERSION=	1.1.1
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/xdg-utils/
COMPONENT_ARCHIVE_HASH= \
	sha256:b0dd63a2576e0bb16f1aa78d6ddf7d6784784a098d4df17161cd6a17c7bc4125
COMPONENT_ARCHIVE_URL=	http://portland.freedesktop.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=      $(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	gnome/interop

TPNO=			32590

# Tests require a window system to be up and running
TEST_TARGET = $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

# Replaces patches/0001-xdg-utils-01-bash.patch
COMPONENT_POST_UNPACK_ACTION += \
    $(GSED) -i -e 's,^\#!/bin/sh$$,\#!/usr/bin/bash,' $(@D)/scripts/*.in

# Cannot find desc/*.xml during build if tree isn't cloned
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Use GNU awk & sed
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# docbook-dtds, xsltproc, & xmlto are used to generate files during the build
REQUIRED_PACKAGES += data/docbook/docbook-dtds
REQUIRED_PACKAGES += developer/documentation-tool/xmlto
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += gnome/zenity
REQUIRED_PACKAGES += library/gnome/gvfs
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-sed
REQUIRED_PACKAGES += x11/x11-server-utilities
