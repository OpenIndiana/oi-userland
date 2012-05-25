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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

GMAKE =				/usr/bin/make

COMPONENT_NAME =		visual-panels-smf
COMPONENT_VERSION =		0.5.11
COMPONENT_SRC =			src

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_TARGETS = 	build
COMPONENT_BUILD_ENV +=		ROOT=$(BUILD_DIR)/prototype/$(MACH)
COMPONENT_BUILD_ENV +=		SRC=$(WS_COMPONENTS)/visual-panels
COMPONENT_BUILD_ENV +=		WS_JAVA=$(BUILD_DIR_32)/java
COMPONENT_BUILD_ENV +=		JAVA_HOME=/usr/java
COMPONENT_BUILD_ENV +=		PATH=$(dir $(CC)):/usr/bin
COMPONENT_BUILD_ENV +=		MACH32=$(MACH32)

COMPONENT_INSTALL_TARGETS =	install
COMPONENT_INSTALL_ENV =		$(COMPONENT_BUILD_ENV)

COMPONENT_TEST_TARGETS =  	test
COMPONENT_TEST_ENV =	  	$(COMPONENT_BUILD_ENV)

# common targets
$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

prep:				$(SOURCE_DIR)/.prep

build:				$(BUILD_32)

install:			$(INSTALL_32)

download::
	@echo 'No downloads for this component'

CLEAN_PATH +=			$(SOURCE_DIR)/.prep

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
