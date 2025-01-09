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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#
#
# Rules and Macros for building opens source software that just uses their
# own make and no autoconf-style tools.
#
# To use these rules, set BUILD_STYLE to justmake and include
# $(WS_MAKE_RULES)/common.mk in your Makefile.
#
# Any additional pre/post configure, build, or install actions can be specified
# in your Makefile by setting them in on of the following macros:
#	COMPONENT_PRE_BUILD_ACTION, COMPONENT_POST_BUILD_ACTION
#	COMPONENT_PRE_INSTALL_ACTION, COMPONENT_POST_INSTALL_ACTION
#
# If component specific make targets need to be used for build or install, they
# can be specified in
#	COMPONENT_BUILD_TARGETS, COMPONENT_INSTALL_TARGETS
#

# Configure
COMPONENT_CONFIGURE_ACTION = true

# Build
COMPONENT_BUILD_CMD = $(GMAKE)
COMPONENT_BUILD_ARGS += $(COMPONENT_BUILD_GMAKE_ARGS)

# Install
COMPONENT_INSTALL_CMD = $(GMAKE)
COMPONENT_INSTALL_ARGS += DESTDIR=$(PROTO_DIR)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Use common rules
USE_COMMON_RULES = yes
