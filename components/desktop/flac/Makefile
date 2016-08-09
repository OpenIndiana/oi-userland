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

BUILD_BITS=		64_and_32
# Upstream requires gcc flags that Studio doesn't support
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		flac
COMPONENT_VERSION=	1.3.1
COMPONENT_PROJECT_URL=	https://xiph.org/flac/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:4773c0099dba767d963fd92143263be338c48702172e8754b9bc5103efe1c56c
COMPONENT_ARCHIVE_URL=	http://downloads.xiph.org/releases/flac/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/multimedia

TPNO=			27270

# tests work but take hours to run and use a lot of disk space
TEST_TARGET = $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-ogg

REQUIRED_PACKAGES += codec/ogg-vorbis
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
