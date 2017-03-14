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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		flex
COMPONENT_VERSION=	2.6.3
COMPONENT_PROJECT_URL=	https://github.com/westes/flex
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:68b2742233e747c462f781462a2a1e299dc6207401dac8f0bbb316f48565c2aa
COMPONENT_ARCHIVE_URL=	https://github.com/westes/flex/releases/download/v2.6.3/flex-2.6.3.tar.gz
COMPONENT_BUGDB=	utility/flex

LDFLAGS = $(CC_BITS)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)

COMPONENT_TEST_ENV +=		PATH=/usr/gnu/bin:/usr/bin

include ../../make-rules/shared-targets.mk

ASLR_MODE=$(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) 

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

