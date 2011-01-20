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
#
# Rules and Macros for building opens source software that just uses their
# own make and no autoconf-style tools.
#
# To use these rules, include ../make-rules/justmake.mk in your Makefile
# and define "build", "install" targets appropriate to building your component.
# Ex:
#
# 	build:		$(BUILD_32) \
#	 		$(BUILD_64)
# 
#	install:	$(INSTALL_32) \
#	 		$(INSTALL_64)
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

CLONEY =	$(WS_TOOLS)/cloney

$(BUILD_DIR_32)/.built:	BITS=32
$(BUILD_DIR_64)/.built:	BITS=64
$(BUILD_DIR_32)/.install:	BITS=32
$(BUILD_DIR_64)/.install:	BITS=64

# set the default target for installation of the component
COMPONENT_INSTALL_TARGETS =	install

# build the configured source
$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			$(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
