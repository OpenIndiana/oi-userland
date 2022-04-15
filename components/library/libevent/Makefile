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

#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libevent
COMPONENT_VERSION=	1.4.15
HUMAN_VERSION=		1.4.15
COMPONENT_SUMMARY=	libevent - an event notification library
COMPONENT_PROJECT_URL=	https://libevent.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-release-$(HUMAN_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e9a32238a98954081d7ed9918d8f799eb4c743fd570749c0721585140dd5de21
COMPONENT_ARCHIVE_URL=	https://github.com/libevent/libevent/archive/refs/tags/release-$(HUMAN_VERSION)-stable.tar.gz
COMPONENT_FMRI=		library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	BSD

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D) && \
	cd $(SOURCE_DIR) && NOCONFIGURE=1 ./autogen.sh )

# The original manpage is in a format that the Solaris man command does
# not understand. Hence it has been manually converted.
#
# List of files from the original package that are not being delivered
# /usr/bin/event_rpcgen.py

CONFIGURE_OPTIONS	+= --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
