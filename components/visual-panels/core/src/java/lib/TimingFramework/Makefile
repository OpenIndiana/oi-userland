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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../../../../../../make-rules/shared-macros.mk
include ../visual-panels.mk

COMPONENT_NAME=		TimingFramework
COMPONENT_VERSION=	1.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:0829f0afbb3569ba506d20f7f508338f9902a1d82ef786cbf93a6839579f0bcf
COMPONENT_ARCHIVE_URL=	http://firebolt.googlecode.com/svn-history/r20/trunk/firebolt/lib/timing-framework/$(COMPONENT_ARCHIVE)

UNPACK_ARGS= -r $(COMPONENT_SRC)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ant.mk

COMPONENT_PREP_ACTION = (cp build.xml $(@D)/)

COMPONENT_BUILD_ARGS 		+= -Ddist=${PROTO_DIR} -Dver=$(COMPONENT_VERSION)
COMPONENT_BUILD_TARGETS += jar

COMPONENT_INSTALL_ARGS 		+= -Ddist=${PROTO_DIR} -Dver=$(COMPONENT_VERSION)
COMPONENT_INSTALL_TARGETS 	+= install

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
