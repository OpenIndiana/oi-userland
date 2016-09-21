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
# To use these rules, include ../make-rules/attpackagemake.mk in your Makefile
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

# Environment variables and arguments passed into the build and install
# environment(s).  These are the initial settings.
COMPONENT_BUILD_ENV += \
    CC_EXPLICIT="$(CC)" \
	PATH=$(shell dirname $(CC)):$(PATH) \
	CC=$(shell basename $(CC)) 
	NPROC="$(NPROC)" 

# This explicitly exports the build type for 32/64 bit distinction 
COMPONENT_BUILD_ARGS = \
						HOSTTYPE="$(HOSTTYPE$(BITS))" \
						CCFLAGS="$(CFLAGS)" \
						LDFLAGS="$(CXXFLAGS)" 

# The install and test process needs the same environment as the build
COMPONENT_INSTALL_ENV = $(COMPONENT_BUILD_ENV)
COMPONENT_TEST_ENV = $(COMPONENT_BUILD_ENV)
COMPONENT_INSTALL_ARGS = HOSTTYPE="$(HOSTTYPE$(BITS))"
COMPONENT_TEST_ARGS = HOSTTYPE="$(HOSTTYPE$(BITS))"

# build the configured source
$(BUILD_DIR)/%/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) \
   		bin/package make $(COMPONENT_BUILD_TARGETS) $(COMPONENT_BUILD_ARGS)
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(@D)
endif
	$(TOUCH) $@

# install the built source into a prototype area
$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	$(RM) -r $(PROTO_DIR)/$(MACH$(BITS)); $(MKDIR) $(PROTO_DIR)/$(MACH$(BITS));
	cd $(@D); $(ENV) $(COMPONENT_INSTALL_ENV) \
		bin/package flat $(COMPONENT_INSTALL_TARGETS) \
		$(COMPONENT_INSTALL_ARGS) \
		$(PROTO_DIR)/$(MACH$(BITS)) $(COMPONENT_INSTALL_PACKAGES) 
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

# test the built source
$(BUILD_DIR)/%/.tested-and-compared:    $(BUILD_DIR)/%/.built
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	-(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		bin/package test $(COMPONENT_TEST_TARGETS) \
		$(COMPONENT_TEST_ARGS) \
		&> $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR)/%/.tested:    $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		bin/package test $(COMPONENT_TEST_TARGETS) \
		$(COMPONENT_TEST_ARGS)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
parfait: build
else
parfait:
	$(MAKE) PARFAIT_BUILD=yes parfait
endif

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
