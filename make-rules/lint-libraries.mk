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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# Rules and Macros for building lint libraries.  This searches for lint
# libraries in the component directory and adds targets to build and install
# them for 32/64 bit.
#
# To use these rules, include $(WS_MAKE_RULES)/lint-libraries.mk in your
# Makefile and add your lint library source in your component directory as
# llib-l{lib}.
#
# Makefile
#    include $(WS_MAKE_RULES)/lint-libraries.mk
#
# llib-l{libname}
#

LINT_LIBRARIES ?= $(wildcard llib-*)

LINT_FLAGS = -nsvx -I$(@D) -I$(SOURCE_DIR)/include -I$(SOURCE_DIR)

# template for lint library rules. new rules will be added automatically
define lintlib-rule
$(BUILD_DIR_32)/$(1).ln:	BITS=32
$(BUILD_DIR_64)/$(1).ln:	BITS=64

$$(BUILD_DIR)/%/$(1).ln:	$(1) $(BUILD_DIR)/%/.installed
	(cd $$(@D) ; $$(LINT) $$(LINT_FLAGS) -o $$(@F:llib-l%.ln=%) ../../$$<)

$$(PROTOUSRLIBDIR)/$(1):	$(1)
	$(INSTALL) -c $$< $$@

$$(PROTOUSRLIBDIR)/$(1).ln:	$$(BUILD_DIR)/$(MACH32)/$(1).ln
	$(INSTALL) -c $$< $$@

$$(PROTOUSRLIBDIR64)/$(1).ln:	$$(BUILD_DIR)/$(MACH64)/$(1).ln
	$(INSTALL) -c $$< $$@

BUILD_32 += $(BUILD_DIR_32)/$(1).ln
BUILD_64 += $(BUILD_DIR_64)/$(1).ln
INSTALL_32 += $(PROTOUSRLIBDIR)/$(1)
INSTALL_32 += $(PROTOUSRLIBDIR)/$(1).ln
INSTALL_64 += $(PROTOUSRLIBDIR64)/$(1).ln
endef

# Generate the lint library rules from the above template
$(foreach lintlib,$(LINT_LIBRARIES),$(eval $(call lintlib-rule,$(lintlib))))
