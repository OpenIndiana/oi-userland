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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, Aurelien Larcher
# Copyright (c) 2018, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		indent
COMPONENT_VERSION=	2.2.12
COMPONENT_FMRI=		developer/gnu-indent
COMPONENT_SUMMARY=	GNU indent - a tool for improving C source code style
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/indent/
COMPONENT_ARCHIVE_HASH=	\
    sha256:b745a5dfc68f86a483d7f96dc1cda7aafd1e78ecba3c7d8ad304709e91e1defb
COMPONENT_ARCHIVE_URL= \
    ftp://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLV2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed to get "gmake test" working.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_BINDIR.64 = $(CONFIGURE_BINDIR.32)

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_TEST_DIR=	$(@D)/regression
# Test expects GNU diff
COMPONENT_TEST_ENV+=	PATH=$(PATH.gnu)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
