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
# Copyright (c) 2012, 2014, Oracle and/or its affiliates. All rights reserved.
#
#
# Rules and Macros for building opens source software that uses AT&T's package
# tool.
#
# To use these rules, set BUILD_STYLE to attpackagemake and include
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
COMPONENT_BUILD_ENV += CC_EXPLICIT="$(CC)"
COMPONENT_BUILD_ENV += PATH=$(dir $(CC)):$(PATH)
COMPONENT_BUILD_ENV += CC=$(notdir $(CC))
COMPONENT_BUILD_ENV += NPROC="$(NPROC)"

COMPONENT_BUILD_CMD = bin/package make

# This explicitly exports the build type for 32/64 bit distinction 
COMPONENT_BUILD_ARGS = \
						HOSTTYPE="$(HOSTTYPE$(BITS))" \
						CCFLAGS="$(CFLAGS)" \
						LDFLAGS="$(CXXFLAGS)" 

# Install
# The install process needs the same environment as the build
COMPONENT_INSTALL_ENV = $(COMPONENT_BUILD_ENV)
COMPONENT_INSTALL_CMD = bin/package flat
COMPONENT_INSTALL_ARGS = HOSTTYPE="$(HOSTTYPE$(BITS))"

COMPONENT_PRE_INSTALL_ACTION += $(RM) -r $(PROTO_DIR)/$(MACH$(BITS)) ;
COMPONENT_PRE_INSTALL_ACTION += $(MKDIR) $(PROTO_DIR)/$(MACH$(BITS)) ;

COMPONENT_INSTALL_ACTION ?= \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) ; $(ENV) $(COMPONENT_INSTALL_ENV) \
		$(COMPONENT_INSTALL_CMD) $(COMPONENT_INSTALL_ARGS) \
		$(COMPONENT_INSTALL_TARGETS) \
		$(PROTO_DIR)/$(MACH$(BITS)) $(COMPONENT_INSTALL_PACKAGES) 

# Test
# The test process needs the same environment as the build
COMPONENT_TEST_ENV = $(COMPONENT_BUILD_ENV)
COMPONENT_TEST_CMD = bin/package test
COMPONENT_TEST_ARGS = HOSTTYPE="$(HOSTTYPE$(BITS))"

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Use common rules
USE_COMMON_RULES = yes
