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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			dejagnu
COMPONENT_VERSION=		1.6.3
COMPONENT_FMRI=			developer/test/dejagnu
COMPONENT_SUMMARY=		DejaGnu - a framework for testing other programs
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_PROJECT_URL=		https://www.gnu.org/software/dejagnu/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:87daefacd7958b4a69f88c6856dbd1634261963c414079d0c371f589cd66a2e3
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_ENV +=	PATH="$(PATH.gnu)"
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/Running/p" ' \
'-e "/\# of /p" '

ASLR_MODE = $(ASLR_ENABLE)

# Manually added dependencies
REQUIRED_PACKAGES += shell/expect

# Auto-generated dependencies

