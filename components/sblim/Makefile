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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cim-client
COMPONENT_VERSION=	1.3.7
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_PROJECT_URL=	http://sblim.wiki.sourceforge.net/CimClient/
COMPONENT_ARCHIVE=	sblim-$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src.zip
COMPONENT_ARCHIVE_HASH=	sha1:6cb6e75b98439e31f32fc5f16f0002f2b1601b50
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/sblim/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ant.mk
include ../../make-rules/ips.mk

# Javadoc files etc are installed here.
PKG_PROTO_DIRS += $(BUILD_DIR_32)

# common targets
build:		$(BUILD_32)

install:	build

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
