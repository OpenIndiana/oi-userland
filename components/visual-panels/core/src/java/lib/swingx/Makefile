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

COMPONENT_NAME=		swingx
COMPONENT_VERSION=	0.9.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:d7f2d0f9d26b60b5a12b4dba29d11343a575f900348b32523153fdfedae22853
COMPONENT_ARCHIVE_URL=	http://java.net/downloads/$(COMPONENT_NAME)/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ant.mk
include ../visual-panels.mk

COMPONENT_BUILD_ARGS 	+= -Ddist=${PROTO_DIR}
COMPONENT_BUILD_TARGETS += jar

# common targets
build:		$(BUILD_32)

install:	build	
	$(MKDIR) $(VP_DIR)
	$(CP) $(BUILD_DIR_32)/dist/$(COMPONENT_NAME).jar \
	      $(VP_DIR)/$(COMPONENT_NAME)-$(COMPONENT_VERSION).jar

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
