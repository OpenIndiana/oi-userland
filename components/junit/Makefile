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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		junit
COMPONENT_VERSION=	4.5
COMPONENT_SRC=		$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha1:75d642adaf15091c7ca9ed54f0f2f058bd9ec653
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/junit/files/junit/4.5/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ant.mk
include ../../make-rules/ips.mk

COMPONENT_BUILD_ARGS 	+= -Ddist=${PROTO_DIR}
COMPONENT_BUILD_ARGS    += -Djavadocdir=${PROTO_DIR}
COMPONENT_BUILD_TARGETS += dist

# common targets
build:		$(BUILD_32)
	
install:	build	
		
test:		$(NO_TESTS)
		
BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
