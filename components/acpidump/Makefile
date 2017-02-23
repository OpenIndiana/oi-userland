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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
COMPILER= gcc
BUILD_ARCH= i386
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		acpidump
COMPONENT_VERSION=	20071116
IPS_COMPONENT_VERSION=	0.2007.11.16
COMPONENT_PROJECT_URL=	http://www.lesswatts.org/projects/acpi/utilities.php
COMPONENT_SRC_NAME=	pmtools
COMPONENT_ARCHIVE_HASH=	\
    sha256:91751774976e39f6237efd0326eb35196a9346220b92ad35894a33283e872748
COMPONENT_ARCHIVE_URL=	http://www.lesswatts.org/patches/linux_acpi/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13294

TPNO=			8848

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_INSTALL_ACTION += $(MKDIR) $(PROTOUSRBINDIR)
COMPONENT_INSTALL_ARGS += DESTDIR=$(PROTOUSRBINDIR)
