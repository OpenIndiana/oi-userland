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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_ARCH= i386
BUILD_BITS= 64 
# component fails to build with Studio
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnu-efi
COMPONENT_VERSION=	3.0
COMPONENT_PROJECT_URL=  http://sourceforge.net/projects/$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION)u.orig.tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:3c0d450d5829204ca05dcb3b2aae772e52c379b7c7e09146759c6315606f934e
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=        library/gnu-efi

TPNO=			26179

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk 

include ../../make-rules/shared-targets.mk

REQUIRED_PACKAGES += developer/gnu-binutils 
REQUIRED_PACKAGES += developer/gcc
