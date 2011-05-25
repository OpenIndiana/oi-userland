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

COMPONENT_NAME=		unison
COMPONENT_VERSION=	2.27.57
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.cis.upenn.edu/~bcpierce/unison
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:9892680d8bd3e3c50031451cc6e77eb5431768ea
COMPONENT_ARCHIVE_URL=	http://www.seas.upenn.edu/~bcpierce/unison//download/releases/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

PKG_PROTO_DIRS += $(BUILD_DIR_32)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_BUILD_ARGS += UISTYLE=gtk2
COMPONENT_BUILD_ARGS += STATIC=true

COMPONENT_TEST_TARGETS=	selftest

# common targets
build:		$(BUILD_32)

install:	$(BUILD_32)

# there are quite a few more interesting test-ish targets
# (like demo) but they mostly seem interactive
test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
