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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, Aurelien Larcher
# Copyright (c) 2020, Michal Nowak
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsigsegv
COMPONENT_VERSION=	2.14
COMPONENT_SUMMARY=	libsigsegv - handling page faults in user mode
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libsigsegv/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:cdac3941803364cf81a908499beb79c200ead60b6b5b40cad124fd1e06caa295
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libsigsegv/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libsigsegv
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

# Test failure
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
