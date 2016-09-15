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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# This file sets up the standard, default options and base requirements for
# userland components.
#

include $(WS_MAKE_RULES)/prep.mk

# Override this to limit builds and publication to a single architecture.
BUILD_ARCH ?= $(MACH)
ifneq ($(strip $(BUILD_ARCH)),$(MACH))
PUBLISH_STAMP= 

target-na:
	@echo "Not available for $(MACH)"

BUILD_TARGET ?= target-na
INSTALL_TARGET ?= target-na
TEST_TARGET ?= target-na
SYSTEM_TEST_TARGET ?= target-na
endif

# Assume components use a configure script-style build by default.
BUILD_STYLE ?= configure
# If not an archive build (i.e. extract and copy) or pkg build (publish only),
# include relevant makefile.
ifneq ($(strip $(BUILD_STYLE)),archive)
ifneq ($(strip $(BUILD_STYLE)),pkg)
include $(WS_MAKE_RULES)/$(strip $(BUILD_STYLE)).mk
endif
endif

ifeq ($(strip $(BUILD_STYLE)),configure)
# Assume these items should always be set in the configure environment.  strip
# is used to work around potential problems with extra blank characters
# inserted into strings during nested configure invocations within builds for
# components such as gdb.
ifneq ($(strip $(CFLAGS)),)
# Only if provided.
CONFIGURE_ENV += CFLAGS="$(strip $(CFLAGS))"
endif
ifneq ($(strip $(CXXFLAGS)),)
# Only if provided.
CONFIGURE_ENV += CXXFLAGS="$(strip $(CXXFLAGS))"
endif
# Always process LDFLAGS.
CONFIGURE_ENV += LDFLAGS="$(strip $(LDFLAGS))"
endif

ifeq ($(strip $(BUILD_STYLE)),justmake)
# Assume these items should always be set in the build environment.
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CXX="$(CXX)"
ifneq ($(strip $(CFLAGS)),)
# Only if provided.
COMPONENT_BUILD_ENV += CFLAGS="$(strip $(CFLAGS))"
endif
ifneq ($(strip $(CXXFLAGS)),)
# Only if provided.
COMPONENT_BUILD_ENV += CXXFLAGS="$(strip $(CXXFLAGS))"
endif
# Always process LDFLAGS.
COMPONENT_BUILD_ENV += LDFLAGS="$(strip $(LDFLAGS))"
endif

# Assume components built with ant do not need ASLR.
ifeq ($(strip $(BUILD_STYLE)),ant)
ASLR_MODE= $(ASLR_NOT_APPLICABLE)
else
# Enable ASLR by default unless target build is NO_ARCH.
ifneq ($(strip $(BUILD_BITS)),NO_ARCH)
ASLR_MODE= $(ASLR_ENABLE)
endif # BUILD_BITS NO_ARCH
endif # BUILD_STYLE ant

# Determine if we should automatically include lint libraries in build and
# install targets based on presence of llib* files in component directory. This
# must be done before defining any common targets since the include affects
# later variable expansion.
LINT_LIBRARIES ?= $(wildcard llib-*)
ifneq ($(strip $(LINT_LIBRARIES)),)
include $(WS_MAKE_RULES)/lint-libraries.mk
endif

# Default targets; to omit a specific target, explicitly set the related target
# variable to empty before including this file or set COMMON_TARGETS=no.
COMMON_TARGETS ?= yes

ifneq ($(strip $(COMMON_TARGETS)),no)
# For ant-based build style, assume that install is provided by simply building
# the component and that no tests are available.
ifeq ($(strip $(BUILD_STYLE)),ant)
INSTALL_TARGET ?= build
TEST_TARGET ?= $(NO_TESTS)
SYSTEM_TEST_TARGET ?= $(NO_TESTS)
endif

# For archive-based build style, assume that the build, install, and test
# targets will be provided.
ifeq ($(strip $(BUILD_STYLE)),archive)
BUILD_TARGET ?=
INSTALL_TARGET ?=
TEST_TARGET ?=
endif

# For pkg-based build style, assume there are no build, install, or test steps;
# just a package to be published.
ifeq ($(strip $(BUILD_STYLE)),pkg)
BUILD_TARGET=
INSTALL_TARGET=
TEST_TARGET=
SYSTEM_TEST_TARGET=
build install:
test system-test:	$(NO_TESTS)
endif

# If TEST_TARGET is NO_TESTS, assume no system tests by default.
ifeq ($(strip $(TEST_TARGET)),$(NO_TESTS))
SYSTEM_TEST_TARGET ?= $(NO_TESTS)
endif

# If TEST_TARGET is SKIP_TEST, assume system tests are skipped by default.
ifeq ($(strip $(TEST_TARGET)),$(SKIP_TEST))
SYSTEM_TEST_TARGET ?= $(SKIP_TEST)
endif

# Otherwise, attempt to define common targets assuming defaults.
BUILD_TARGET ?= $(BUILD_$(MK_BITS))
ifneq ($(strip $(BUILD_TARGET)),)
build:          $(BUILD_TARGET)
endif

INSTALL_TARGET ?= $(INSTALL_$(MK_BITS))
ifneq ($(strip $(INSTALL_TARGET)),)
install:        $(INSTALL_TARGET)
endif

TEST_TARGET ?= $(TEST_$(MK_BITS))
ifneq ($(strip $(TEST_TARGET)),)
test:           $(TEST_TARGET)
endif

# For the system-test target, assume that none have been implemented.
SYSTEM_TEST_TARGET ?= $(SYSTEM_TESTS_NOT_IMPLEMENTED)
ifneq ($(strip $(SYSTEM_TEST_TARGET)),)
system-test:    $(SYSTEM_TEST_TARGET)
endif
endif # COMMON_TARGETS

# Always needed; every component builds packages.
include $(WS_MAKE_RULES)/ips.mk

# Determine if we should automatically add files directory to PKG_PROTO_DIRS.
ifeq ($(wildcard files),files)
PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files
endif

# Add bit and mach-specific logic to general actions.
COMPONENT_PRE_CONFIGURE_ACTION += $(COMPONENT_PRE_CONFIGURE_ACTION.$(BITS))
COMPONENT_PRE_CONFIGURE_ACTION += $(COMPONENT_PRE_CONFIGURE_ACTION.$(MACH))
COMPONENT_POST_CONFIGURE_ACTION += $(COMPONENT_POST_CONFIGURE_ACTION.$(BITS))
COMPONENT_POST_CONFIGURE_ACTION += $(COMPONENT_POST_CONFIGURE_ACTION.$(MACH))
COMPONENT_PRE_BUILD_ACTION += $(COMPONENT_PRE_BUILD_ACTION.$(BITS))
COMPONENT_PRE_BUILD_ACTION += $(COMPONENT_PRE_BUILD_ACTION.$(MACH))
COMPONENT_POST_BUILD_ACTION += $(COMPONENT_POST_BUILD_ACTION.$(BITS))
COMPONENT_POST_BUILD_ACTION += $(COMPONENT_POST_BUILD_ACTION.$(MACH))
COMPONENT_PRE_INSTALL_ACTION += $(COMPONENT_PRE_INSTALL_ACTION.$(BITS))
COMPONENT_PRE_INSTALL_ACTION += $(COMPONENT_PRE_INSTALL_ACTION.$(MACH))
COMPONENT_POST_INSTALL_ACTION += $(COMPONENT_POST_INSTALL_ACTION.$(BITS))
COMPONENT_POST_INSTALL_ACTION += $(COMPONENT_POST_INSTALL_ACTION.$(MACH))
COMPONENT_PRE_TEST_ACTION += $(COMPONENT_PRE_TEST_ACTION.$(BITS))
COMPONENT_PRE_TEST_ACTION += $(COMPONENT_PRE_TEST_ACTION.$(MACH))
COMPONENT_POST_TEST_ACTION += $(COMPONENT_POST_TEST_ACTION.$(BITS))
COMPONENT_POST_TEST_ACTION += $(COMPONENT_POST_TEST_ACTION.$(MACH))
