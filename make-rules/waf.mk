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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
#
# Rules and Macros for building opens source software that uses the waf
# build system from https://waf.io/
#
# To use these rules, include $(WS_MAKE_RULES)/waf.mk in your Makefile
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

# Defaults to looking for waf script in top level of cloned source
WAF = $(PYTHON) waf

CONFIGURE_PREFIX =	/usr

CONFIGURE_BINDIR.32 =	$(CONFIGURE_PREFIX)/bin
CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin/$(MACH64)
CONFIGURE_LIBDIR.32 =	$(CONFIGURE_PREFIX)/lib
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_PREFIX)/lib/$(MACH64)
CONFIGURE_SBINDIR.32 =	$(CONFIGURE_PREFIX)/sbin
CONFIGURE_SBINDIR.64 =	$(CONFIGURE_PREFIX)/sbin/$(MACH64)
CONFIGURE_MANDIR =	$(CONFIGURE_PREFIX)/share/man
CONFIGURE_LOCALEDIR =	$(CONFIGURE_PREFIX)/share/locale

CONFIGURE_DEFAULT_DIRS?=yes
CONFIGURE_OPTIONS += --prefix=$(CONFIGURE_PREFIX)
ifeq ($(CONFIGURE_DEFAULT_DIRS),yes)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
ifeq ($(INITIAL_BITS),64)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.32)
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.32)
else
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
endif
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
endif
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH))
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH).$(BITS))

CONFIGURE_ENV += CC="$(CC) $(CC_BITS)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CXX="$(CXX) $(CC_BITS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYTHONDIR="$(PYTHON_LIB)"
CONFIGURE_ENV += PYTHONARCHDIR="$(PYTHON_VENDOR_PACKAGES)"

# configure the unpacked source
COMPONENT_CONFIGURE_TARGETS ?= configure

$(BUILD_DIR_32)/.configured:		BITS=32
$(BUILD_DIR_64)/.configured:		BITS=64
$(BUILD_DIR)/$(MACH32)-%/.configured:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.configured:	BITS=64
$(foreach pyver, $(PYTHON_VERSIONS), \
    $(eval $(BUILD_DIR)/%-$(pyver)/.configured: PYTHON_VERSION=$(pyver)) \
)

$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; $(ENV) $(CONFIGURE_ENV) \
		$(WAF) $(COMPONENT_CONFIGURE_TARGETS) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

# build the configured source
COMPONENT_BUILD_TARGETS ?= build

$(BUILD_DIR_32)/.built:			BITS=32
$(BUILD_DIR_64)/.built:			BITS=64
$(BUILD_DIR)/$(MACH32)-%/.built:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.built:	BITS=64
$(foreach pyver, $(PYTHON_VERSIONS), \
    $(eval $(BUILD_DIR)/%-$(pyver)/.built: PYTHON_VERSION=$(pyver)) \
)

$(BUILD_DIR)/%/.built:	$(BUILD_DIR)/%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(WAF) $(COMPONENT_BUILD_TARGETS) $(COMPONENT_BUILD_ARGS))
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) $(@D)
endif
	$(TOUCH) $@

# If BUILD_STYLE is set, provide a default configure target.
ifeq   ($(strip $(BUILD_STYLE)),waf)
configure:	$(CONFIGURE_$(MK_BITS))
endif

# install the built source into a prototype area
COMPONENT_INSTALL_ARGS += --destdir=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS += $(COMPONENT_INSTALL_ARGS.$(BITS))

$(BUILD_DIR_32)/.installed:		BITS=32
$(BUILD_DIR_64)/.installed:		BITS=64
$(BUILD_DIR)/$(MACH32)-%/.installed:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.installed:	BITS=64
$(foreach pyver, $(PYTHON_VERSIONS), \
    $(eval $(BUILD_DIR)/%-$(pyver)/.installed: PYTHON_VERSION=$(pyver)) \
)

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_INSTALL_ENV) \
		 $(WAF) $(COMPONENT_INSTALL_TARGETS) $(COMPONENT_INSTALL_ARGS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

# test the built source
COMPONENT_TEST_CMD = $(WAF)
COMPONENT_TEST_TARGETS = test

$(BUILD_DIR_32)/.tested-and-compared:		BITS=32
$(BUILD_DIR_64)/.tested-and-compared:		BITS=64
$(BUILD_DIR)/$(MACH32)-%/.tested-and-compared:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared:	BITS=64
$(foreach pyver, $(PYTHON_VERSIONS), \
    $(eval $(BUILD_DIR)/%-$(pyver)/.tested-and-compared: PYTHON_VERSION=$(pyver)) \
)

$(BUILD_DIR)/%/.tested-and-compared:    $(BUILD_DIR)/%/.built
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(COMPONENT_PRE_TEST_ACTION)
	-(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_TARGETS) $(COMPONENT_TEST_ARGS)) \
		&> $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR_32)/.tested:		BITS=32
$(BUILD_DIR_64)/.tested:		BITS=64
$(BUILD_DIR)/$(MACH32)-%/.tested:	BITS=32
$(BUILD_DIR)/$(MACH64)-%/.tested:	BITS=64
$(foreach pyver, $(PYTHON_VERSIONS), \
    $(eval $(BUILD_DIR)/%-$(pyver)/.tested: PYTHON_VERSION=$(pyver)) \
)

$(BUILD_DIR)/%/.tested:    $(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_TEST_ACTION)
	(cd $(COMPONENT_TEST_DIR) ; \
		$(COMPONENT_TEST_ENV_CMD) $(COMPONENT_TEST_ENV) \
		$(COMPONENT_TEST_CMD) \
		$(COMPONENT_TEST_ARGS) $(COMPONENT_TEST_TARGETS))
	$(COMPONENT_POST_TEST_ACTION)
	$(COMPONENT_TEST_CLEANUP)
	$(TOUCH) $@

# Test the installed packages.  The targets above depend on .built which
# means $(CLONEY) has already run.  System-test needs cloning but not
# building; thus ideally, we would want to depend on .cloned here and below,
# but since we don't have that, we depend on .prep and run $(CLONEY) here.
$(BUILD_DIR)/%/.system-tested-and-compared:    $(SOURCE_DIR)/.prep
	$(RM) -rf $(COMPONENT_TEST_BUILD_DIR)
	$(MKDIR) $(COMPONENT_TEST_BUILD_DIR)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_SYSTEM_TEST_ACTION)
	-(cd $(COMPONENT_SYSTEM_TEST_DIR) ; \
		$(COMPONENT_SYSTEM_TEST_ENV_CMD) $(COMPONENT_SYSTEM_TEST_ENV) \
		$(COMPONENT_SYSTEM_TEST_CMD) \
		$(COMPONENT_SYSTEM_TEST_ARGS) $(COMPONENT_SYSTEM_TEST_TARGETS)) \
		&> $(COMPONENT_TEST_OUTPUT)
	$(COMPONENT_POST_SYSTEM_TEST_ACTION)
	$(COMPONENT_TEST_CREATE_TRANSFORMS)
	$(COMPONENT_TEST_PERFORM_TRANSFORM)
	$(COMPONENT_TEST_COMPARE)
	$(COMPONENT_SYSTEM_TEST_CLEANUP)
	$(TOUCH) $@

$(BUILD_DIR)/%/.system-tested:    $(SOURCE_DIR)/.prep
	$(CLONEY) $(SOURCE_DIR) $(@D)
	$(COMPONENT_PRE_SYSTEM_TEST_ACTION)
	(cd $(COMPONENT_SYSTEM_TEST_DIR) ; \
		$(COMPONENT_SYSTEM_TEST_ENV_CMD) $(COMPONENT_SYSTEM_TEST_ENV) \
		$(COMPONENT_SYSTEM_TEST_CMD) \
		$(COMPONENT_SYSTEM_TEST_ARGS) $(COMPONENT_SYSTEM_TEST_TARGETS))
	$(COMPONENT_POST_SYSTEM_TEST_ACTION)
	$(COMPONENT_SYSTEM_TEST_CLEANUP)
	$(TOUCH) $@

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
parfait: build
else
parfait:
	$(MAKE) PARFAIT_BUILD=yes parfait
endif
